// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/analysis/onboard_analysis.hpp"

#include <cmath>
#include <optional>

#include "Eigen/Core"
#include "GeographicLib/TransverseMercator.hpp"
#include "freertos/queue.h"
#include "scope_guard/scope_guard.hpp"

#include "common/macros.hpp"
#include "common/task.hpp"
#include "common/times.hpp"
#include "device/gps_utils.hpp"
#include "map/utils.hpp"
#include "math/polyfill.hpp"
#include "math/segment2.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

namespace analysis {

namespace {

constexpr char TAG[] = "onboard";
constexpr int kOnboardAnalysisStackSize = 4096;
constexpr int kOnboardAnalysisGpsQueueSize = 10;

constexpr double kMapDetectMaxRadiusM = 10000.0;
constexpr int kMapDetectMinRefreshIntervalMs = 5000;
constexpr double kMapDetectMinRefreshDistanceM = 5.0;

constexpr int kPoseHistoryDepth = 10;

}  // namespace

OnboardAnalysis::OnboardAnalysis()
    : pose_history_(kPoseHistoryDepth),
      gps_queue_(CHECK_NOTNULL(xQueueCreate(kOnboardAnalysisGpsQueueSize, sizeof(ParsedNmea)))) {
  map_index_ = map::MapIndex::GetInstance();
  localizer_ = std::make_unique<l10n::Localizer>();
}

void OnboardAnalysis::Reset() {
  gps_collector_.Reset();
  last_map_detect_pose_.reset();
}

esp_err_t OnboardAnalysis::Start() {
  Reset();
  return Task::SpawnSame(TAG, kOnboardAnalysisStackSize, kPriorityOnboardAnalysis);
}

void OnboardAnalysis::Run() {
  while (true) {
    ParsedNmea nmea{};
    xQueueReceive(gps_queue_, &nmea, portMAX_DELAY);
    const std::optional<GpsPose> gps_pose = gps_collector_.Update(nmea);
    if (!gps_pose) {
      continue;
    }

    const bool new_map_loaded = DetectAndLoadMap(*gps_pose);
    if (new_map_loaded) {
      localizer_->SetMap(map_.get());
    }
    if (!map_) {
      continue;
    }

    localizer_->UpdateGps(*gps_pose);
    const MapLocalPose pose = localizer_->Compute();
    pose_history_.push_back(pose);
  }
}

bool OnboardAnalysis::DetectAndLoadMap(const GpsPose& pose) {
  // don't detect too often / too close to the last point
  if (last_map_detect_pose_) {
    if (pose.timestamp_ms - last_map_detect_pose_->timestamp_ms < kMapDetectMinRefreshIntervalMs) {
      return false;
    }
    const double distance =
        map::GeodesicDistance(pose.llh.head<2>(), last_map_detect_pose_->llh.head<2>());
    if (distance < kMapDetectMinRefreshDistanceM) {
      return false;
    }
  }
  last_map_detect_pose_ = pose;
  if (map_index_->entries().empty()) {
    // TODO: properly deal with delayed loads
    return false;
  }

  auto [entry, distance] = map_index_->GetNearestMap(pose.llh.head<2>());
  if (!entry || entry->name == map_name_ || distance > kMapDetectMaxRadiusM) {
    return false;
  }
  map_ = map::Map::FromFile(entry->path);
  return true;
}

}  // namespace analysis
