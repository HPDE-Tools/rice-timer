// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common/times.hpp"
#include "device/gps_utils.hpp"
#include "interface/localization.hpp"

namespace app {

class OnboardAnalysis;
extern std::unique_ptr<OnboardAnalysis> g_onboard_analysis;

TaskHandle_t GetOnboardAnalysisTask();
esp_err_t SetupOnboardAnalysis();
esp_err_t StartOnboardAnalysisTask();
void ResetOnboardAnalysis();
void OnboardAnalysisUpdateGps(const ParsedNmea& nmea);

}  // namespace app
