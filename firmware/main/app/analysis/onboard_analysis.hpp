// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common/task.hpp"
#include "common/times.hpp"
#include "device/gps_utils.hpp"
#include "interface/localization.hpp"

namespace app {

class OnboardAnalysis : public Task {
 public:
  OnboardAnalysis();

  void Reset();

  esp_err_t Start();

  void UpdateGps(const ParsedNmea& nmea) { xQueueSendToBack(gps_queue_, &nmea, 0); }

 protected:
  void Run() override;

 private:
  QueueHandle_t gps_queue_{};
};

extern std::unique_ptr<OnboardAnalysis> g_onboard_analysis;

esp_err_t SetupOnboardAnalysis();
esp_err_t StartOnboardAnalysisTask();
void ResetOnboardAnalysis();
void OnboardAnalysisUpdateGps(const ParsedNmea& nmea);

}  // namespace app
