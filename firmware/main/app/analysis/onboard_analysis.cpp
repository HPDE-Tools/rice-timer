// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/analysis/onboard_analysis.hpp"

#include <cmath>
#include <optional>

#include "Eigen/Core"
#include "GeographicLib/TransverseMercator.hpp"
#include "fmt/core.h"
#include "freertos/queue.h"
#include "scope_guard/scope_guard.hpp"

#include "common/macros.hpp"
#include "common/perf.hpp"
#include "common/task.hpp"
#include "common/times.hpp"
#include "device/capture_manager.hpp"
#include "device/gps_utils.hpp"
#include "map/utils.hpp"
#include "math/polyfill.hpp"
#include "math/segment2.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

DEFINE_PERF(onboard_analysis);

using ricetimer::proto::CheckpointType;

namespace analysis {

namespace {

constexpr char TAG[] = "onboard";
constexpr int kOnboardAnalysisStackSize = 4096;
constexpr int kOnboardAnalysisGpsQueueSize = 10;

constexpr double kMapDetectMaxRadiusM = 10000.0;
constexpr int kMapDetectMinRefreshIntervalMs = 5000;
constexpr double kMapDetectMinRefreshDistanceM = 25.0;

constexpr int kPoseHistoryDepth = 10;

}  // namespace

OnboardAnalysis::OnboardAnalysis()
    : pose_history_(kPoseHistoryDepth),
      gps_queue_(CHECK_NOTNULL(xQueueCreate(kOnboardAnalysisGpsQueueSize, sizeof(ParsedNmea)))) {
  localizer_ = std::make_unique<l10n::Localizer>();
  checkpoint_detector_ = std::make_unique<CheckpointDetector>();
}

void OnboardAnalysis::Reset() {
  gps_collector_.Reset();
  localizer_->Reset();
  pose_history_.clear();
  lap_timer_.Reset();
  last_map_detect_pose_.reset();

  ui::g_model.lap_timer.reset();
}

esp_err_t OnboardAnalysis::Start() {
  Reset();
  return Task::SpawnSame(TAG, kOnboardAnalysisStackSize, kPriorityOnboardAnalysis);
}

// NMEA => GPS pose => map det result => l10n result => l10n history
// l10n result/history => checkpoint det result => lap time event
//                     => ...
void OnboardAnalysis::Run() {
  while (true) {
    ParsedNmea nmea{};
    xQueueReceive(gps_queue_, &nmea, portMAX_DELAY);

    const std::optional<GpsPose> gps_pose = gps_collector_.Update(nmea);
    if (!gps_pose || !gps_pose->is_valid) {
      continue;
    }

    SCOPE_PERF(onboard_analysis);

    (void)DetectAndLoadMap(*gps_pose);
    if (!map_) {
      continue;
    }

    localizer_->UpdateGps(*gps_pose);
    const MapLocalPose pose = localizer_->Compute();
    pose_history_.push_back(pose);
    if (l10n_result_handler_) {
      l10n_result_handler_(pose);
    }

    const std::optional<CheckpointDetector::Result> detection =
        checkpoint_detector_->Detect(pose_history_);
    if (!detection) {
      continue;
    }
    const auto& checkpoint = *(*map_->checkpoints())[detection->checkpoint_index];
    if (checkpoint_handler_) {
      checkpoint_handler_(*detection, checkpoint);
    }

    if (checkpoint.type() == CheckpointType::StartFinish) {
      lap_timer_.HitStartFinish(detection->timestamp_ms);
      UpdateLapTimerUi();
    }
  }
}

bool OnboardAnalysis::DetectAndLoadMap(const GpsPose& pose) {
  auto map_index = map::MapIndex::GetInstance();
  if (map_index->entries().empty()) {
    // TODO: properly deal with delayed loads
    // ESP_LOGE(TAG, "DetectAndLoadMap empty");
    return false;
  }

  // don't detect too often / too close to the last point
  if (last_map_detect_pose_) {
    if (pose.timestamp_ms - last_map_detect_pose_->timestamp_ms < kMapDetectMinRefreshIntervalMs) {
      return false;
    }
    const double distance =
        map::GeodesicDistance(pose.llh.head<2>(), last_map_detect_pose_->llh.head<2>());
    // TODO: hysterisis
    if (distance < kMapDetectMinRefreshDistanceM) {
      return false;
    }
  }
  last_map_detect_pose_ = pose;

  auto [entry, distance] = map_index->GetNearestMap(pose.llh.head<2>());
  if (!entry || entry->name == map_name_ || distance > kMapDetectMaxRadiusM) {
    return false;
  }
  map_ = map::Map::FromFile(entry->path);  // TODO: handle load fail
  map_name_ = entry->name;
  UpdateMapRefs();
  return true;
}

void OnboardAnalysis::UpdateMapRefs() {
  const map::Map* map = map_.get();
  localizer_->SetMap(map);
  checkpoint_detector_->SetMap(map);
  if (map) {
    ui::g_model.map_name = map_name_;
  } else {
    lap_timer_.Reset();
    ui::g_model.map_name.clear();
    ui::g_model.lap_timer.reset();
  }
}

void OnboardAnalysis::UpdateLapTimerUi() {
  if (!ui::g_model.lap_timer) {
    ui::g_model.lap_timer.emplace();
  }
  auto& ui_lap_timer = *ui::g_model.lap_timer;
  ui_lap_timer.num_complete_laps = lap_timer_.num_complete_laps();
  ui_lap_timer.curr_lap_start_timestamp_ms = lap_timer_.curr_lap_start_timestamp_ms();
  ui_lap_timer.min_lap_duration_ms = lap_timer_.min_lap_duration_ms();
  ui_lap_timer.min_lap_index = lap_timer_.min_lap_index();
  if (lap_timer_.num_complete_laps() > 0) {
    ui_lap_timer.last_lap_duration_ms = lap_timer_.complete_lap_durations_ms().back();
  } else {
    ui_lap_timer.last_lap_duration_ms.reset();
  }
}

}  // namespace analysis
