// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/onboard_analysis.hpp"

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

constexpr char TAG[] = "lap";
constexpr int kOnboardAnalysisStackSize = 4096;
constexpr int kOnboardAnalysisGpsQueueSize = 10;

}  // namespace

class OnboardAnalysis : public Task {
 public:
  OnboardAnalysis()
      : gps_queue_(CHECK_NOTNULL(
            xQueueCreate(kOnboardAnalysisGpsQueueSize, sizeof(minmea_sentence_rmc)))) {}

  virtual ~OnboardAnalysis() { Task::Kill(); }

  void Reset() {
    num_laps_ = 0;
    lap_start_time_ms_ = NowUnixMs();
    last_gps_pos_ = {NAN, NAN};
    ui::g_model.num_laps = 0;
    ui::g_model.lap_start_time_ms = std::nullopt;
  }

  void UpdateGps(const ParsedNmea& nmea) { xQueueSendToBack(gps_queue_, &nmea, 0); }

  esp_err_t Start() {
    Reset();
    return Task::SpawnSame(TAG, kOnboardAnalysisStackSize, kPriorityOnboardAnalysis);
  }

  int num_laps() const { return num_laps_; }
  int64_t lap_start_ms() const { return lap_start_time_ms_; }

 protected:
  void Run() override {
    while (true) {
      minmea_sentence_rmc rmc{};
      xQueueReceive(gps_queue_, &rmc, portMAX_DELAY);
      if (!rmc.valid) {
        continue;
      }
    }
  }

 private:
  QueueHandle_t gps_queue_{};

  int num_laps_ = 0;
  int64_t lap_start_time_ms_ = 0;
  Eigen::Vector2f last_gps_pos_;
  int64_t last_gps_time_ms_;
};

////////////////////////////////////////

std::unique_ptr<OnboardAnalysis> g_onboard_analysis{};

TaskHandle_t GetOnboardAnalysisTask() {
  return g_onboard_analysis ? g_onboard_analysis->handle() : nullptr;
}

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

void OnboardAnalysisUpdateGps(const ParsedNmea& nmea) {
  if (g_onboard_analysis) {
    g_onboard_analysis->UpdateGps(nmea);
  }
}

}  // namespace app
