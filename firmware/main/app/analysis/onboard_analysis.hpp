// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app/analysis/checkpoint_detector.hpp"
#include "app/analysis/lap_timer.hpp"
#include "common/circular_buffer.hpp"
#include "common/task.hpp"
#include "common/times.hpp"
#include "device/gps_utils.hpp"
#include "interface/localization.hpp"
#include "localization/gps_collector.hpp"
#include "localization/localizer.hpp"
#include "map/map.hpp"
#include "map/map_index.hpp"

namespace analysis {

class OnboardAnalysis : public Task {
 public:
  OnboardAnalysis();

  void Reset();
  esp_err_t Start();

  void UpdateGps(const ParsedNmea& nmea) { xQueueSendToBack(gps_queue_, &nmea, 0); }
  void UpdateImu(const ImuReading& imu);

 protected:
  void Run() override;

 private:
  map::MapIndex* map_index_ = nullptr;
  std::unique_ptr<map::Map> map_ = nullptr;
  std::string map_name_{};

  l10n::GpsCollector gps_collector_{};
  std::unique_ptr<l10n::Localizer> localizer_ = nullptr;  // depends on map_
  CircularBuffer<MapLocalPose> pose_history_;

  std::unique_ptr<CheckpointDetector> checkpoint_detector_ = nullptr;
  LapTimer lap_timer_{};

  // makeshift map region detection states
  std::optional<GpsPose> last_map_detect_pose_{};

  QueueHandle_t gps_queue_{};

  bool DetectAndLoadMap(const GpsPose& pose);
};

extern std::unique_ptr<OnboardAnalysis> g_onboard_analysis;

esp_err_t SetupOnboardAnalysis();
esp_err_t StartOnboardAnalysisTask();
void ResetOnboardAnalysis();
void OnboardAnalysisUpdateGps(const ParsedNmea& nmea);

}  // namespace analysis
