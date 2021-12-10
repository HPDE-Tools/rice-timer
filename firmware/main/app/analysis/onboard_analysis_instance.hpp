// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"

#include "device/gps_utils.hpp"
#include "interface/localization.hpp"

namespace analysis {
class OnboardAnalysis;
}  // namespace analysis

namespace app {

extern std::unique_ptr<analysis::OnboardAnalysis> g_onboard_analysis;

esp_err_t SetupOnboardAnalysis();
esp_err_t StartOnboardAnalysisTask();
void ResetOnboardAnalysis();
void OnboardAnalysisUpdateGps(const ParsedNmea& nmea);
void OnboardAnalysisUpdateImu(const ImuReading& imu);

}  // namespace app
