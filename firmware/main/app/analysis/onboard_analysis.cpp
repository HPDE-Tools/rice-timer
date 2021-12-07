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
#include "math/polyfill.hpp"
#include "math/segment2.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "onboard";
constexpr int kOnboardAnalysisStackSize = 4096;
constexpr int kOnboardAnalysisGpsQueueSize = 10;

}  // namespace

OnboardAnalysis::OnboardAnalysis()
    : gps_queue_(
          CHECK_NOTNULL(xQueueCreate(kOnboardAnalysisGpsQueueSize, sizeof(minmea_sentence_rmc)))) {}

void OnboardAnalysis::Reset() {
  // TODO
}

esp_err_t OnboardAnalysis::Start() {
  Reset();
  return Task::SpawnSame(TAG, kOnboardAnalysisStackSize, kPriorityOnboardAnalysis);
}

void OnboardAnalysis::Run() {
  while (true) {
    minmea_sentence_rmc rmc{};
    xQueueReceive(gps_queue_, &rmc, portMAX_DELAY);
    if (!rmc.valid) {
      continue;
    }
  }
}

////////////////////////////////////////

std::unique_ptr<OnboardAnalysis> g_onboard_analysis{};

esp_err_t SetupOnboardAnalysis() {
  g_onboard_analysis = std::make_unique<OnboardAnalysis>();
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

}  // namespace app
