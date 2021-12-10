// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/analysis/onboard_analysis_instance.hpp"

#include "app/analysis/onboard_analysis.hpp"
#include "common/macros.hpp"

namespace app {

std::unique_ptr<analysis::OnboardAnalysis> g_onboard_analysis{};

esp_err_t SetupOnboardAnalysis() {
  g_onboard_analysis = std::make_unique<analysis::OnboardAnalysis>();
  return g_onboard_analysis ? ESP_OK : ESP_FAIL;
}

esp_err_t StartOnboardAnalysisTask() {
  CHECK(g_onboard_analysis != nullptr);
  return g_onboard_analysis->Start();
}

void ResetOnboardAnalysis() {
  if (g_onboard_analysis) {
    g_onboard_analysis->Reset();
  }
}

void OnboardAnalysisUpdateGps(const ParsedNmea& nmea) {
  if (g_onboard_analysis) {
    g_onboard_analysis->UpdateGps(nmea);
  }
}
void OnboardAnalysisUpdateImu(const ImuReading& imu) {
  if (g_onboard_analysis) {
    g_onboard_analysis->UpdateImu(imu);
  }
}

}  // namespace app
