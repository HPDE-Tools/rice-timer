// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/analysis/onboard_analysis_instance.hpp"

#include "fmt/chrono.h"
#include "fmt/core.h"

#include "app/analysis/checkpoint_detector.hpp"
#include "app/analysis/onboard_analysis.hpp"
#include "app/logger_instance.hpp"
#include "common/macros.hpp"

using fmt::print;

namespace app {

namespace {

void HandleL10nResult(const MapLocalPose& pose) {
  // print("{:+9.2f},{:+9.2f},{:+9.2f}\n", pose.enh[0], pose.enh[1], pose.enh[2]);  // DEBUG
}

void HandleCheckpoint(
    const analysis::CheckpointDetector::Result& detection,
    const ricetimer::proto::Checkpoint& checkpoint) {
  const TimeParts cal = ToParts(static_cast<time_t>(detection.timestamp_ms / 1000));
  fmt::print(
      "checkpoint #{} @ {:%T}.{:03}",
      detection.checkpoint_index,
      cal,
      detection.timestamp_ms % 1000);  // DEBUG

  // TODO: configurable triggering
  if (g_logger && g_logger->state() == io::Logger::State::kStopped) {
    StartNewLoggingSession();
  }
}

}  // namespace

std::unique_ptr<analysis::OnboardAnalysis> g_onboard_analysis{};

esp_err_t SetupOnboardAnalysis() {
  g_onboard_analysis = std::make_unique<analysis::OnboardAnalysis>();
  return g_onboard_analysis ? ESP_OK : ESP_FAIL;
}

esp_err_t StartOnboardAnalysisTask() {
  CHECK(g_onboard_analysis != nullptr);
  g_onboard_analysis->set_l10n_pose_handler(HandleL10nResult);
  g_onboard_analysis->set_checkpoint_handler(HandleCheckpoint);
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

#include "app/analysis/onboard_analysis_sim_command.inl.cpp"
