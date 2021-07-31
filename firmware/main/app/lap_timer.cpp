// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/lap_timer.hpp"

#include <cmath>
#include <optional>

#include "Eigen/Core"
#include "GeographicLib/TransverseMercator.hpp"
#include "freertos/queue.h"
#include "scope_guard/scope_guard.hpp"

#include "common/macros.hpp"
#include "common/task.hpp"
#include "common/times.hpp"
#include "math/polyfill.hpp"
#include "math/segment2.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "lap";
constexpr int kLapTimerStackSize = 4096;
constexpr int kLapTimerGpsQueueSize = 10;

// NOTE(summivox): Hard-coded fake test track (CW) start-finish line

constexpr double kStartLeftLat = 37.540250;
constexpr double kStartLeftLon = -122.061657;
constexpr double kStartRightLat = 37.540089;
constexpr double kStartRightLon = -122.061477;
constexpr double kOriginLat = std::midpoint(kStartLeftLat, kStartRightLat);
constexpr double kOriginLon = std::midpoint(kStartLeftLon, kStartRightLon);

}  // namespace

class LapTimer : public Task {
 public:
  LapTimer()
      : gps_queue_(
            CHECK_NOTNULL(xQueueCreate(kLapTimerGpsQueueSize, sizeof(minmea_sentence_rmc)))) {
    double unused_x;
    ltm_.Forward(kOriginLon, kOriginLat, kOriginLon, /*out*/ unused_x, /*out*/ origin_y_);
    start_finish_ = {
        LatLonToLtm(kStartLeftLat, kStartLeftLon), LatLonToLtm(kStartRightLat, kStartRightLon)};
  }

  virtual ~LapTimer() { Task::Kill(); }

  void Reset() {
    num_laps_ = 0;
    lap_start_time_ms_ = NowUnixMs();
    last_gps_pos_ = {NAN, NAN};
    ui::g_model.num_laps = 0;
    ui::g_model.lap_start_time_ms = std::nullopt;
  }

  void UpdateGps(const minmea_sentence_rmc& rmc) { xQueueSendToBack(gps_queue_, &rmc, 0); }

  esp_err_t Start() {
    Reset();
    return Task::SpawnSame(TAG, kLapTimerStackSize, kPriorityLapTimer);
  }

  Eigen::Vector2f LatLonToLtm(double lat, double lon) {
    double x = NAN;
    double y = NAN;
    ltm_.Forward(kOriginLon, lat, lon, /*out*/ x, /*out*/ y);
    y -= origin_y_;
    return {x, y};
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
      const Eigen::Vector2f curr_gps_pos =
          LatLonToLtm(minmea_tocoord(&rmc.latitude), minmea_tocoord(&rmc.longitude));
      // TODO(summivox): properly pass through timestamp
      const int64_t curr_gps_time_ms = ToMilliseconds(ToUnixWithUs(2000, rmc.date, rmc.time));
      ui::g_model.ltm_x = curr_gps_pos.x();
      ui::g_model.ltm_y = curr_gps_pos.y();
      SCOPE_EXIT {
        last_gps_pos_ = curr_gps_pos;
        last_gps_time_ms_ = curr_gps_time_ms;
      };
      if (!std::isfinite(last_gps_pos_.x())) {
        continue;
      }
      const math::Segment2f gps_step{last_gps_pos_, curr_gps_pos};
      float step_ratio = NAN;
      if (math::Intersect(
              start_finish_,
              gps_step,
              /*ratio1*/ (float*)nullptr,
              &step_ratio,
              /*point*/ (Eigen::Vector2f*)nullptr)) {
        // TODO(summivox): filter by normal vector, ...
        num_laps_++;
        lap_start_time_ms_ =
            last_gps_time_ms_ +
            static_cast<int64_t>(std::round((curr_gps_time_ms - last_gps_time_ms_) * step_ratio));

        ui::g_model.num_laps = num_laps_;
        ui::g_model.lap_start_time_ms = lap_start_time_ms_;

        ESP_LOGW(TAG, "cross start finish line: lap #%d @ %lld", num_laps_, lap_start_time_ms_);
      }
    }
  }

 private:
  GeographicLib::TransverseMercator ltm_{
      GeographicLib::Constants::WGS84_a(),
      GeographicLib::Constants::WGS84_f(),
      /*scale*/ 1.0,
  };
  double origin_y_;
  QueueHandle_t gps_queue_{};

  math::Segment2f start_finish_;

  int num_laps_ = 0;
  int64_t lap_start_time_ms_ = 0;
  Eigen::Vector2f last_gps_pos_;
  int64_t last_gps_time_ms_;
};

////////////////////////////////////////

std::unique_ptr<LapTimer> g_lap_timer{};

TaskHandle_t GetLapTimerTask() { return g_lap_timer ? g_lap_timer->handle() : nullptr; }

esp_err_t SetupLapTimer() {
  g_lap_timer = std::make_unique<LapTimer>();
  return g_lap_timer ? ESP_OK : ESP_FAIL;
}

esp_err_t StartLapTimerTask() {
  CHECK(g_lap_timer != nullptr);
  return g_lap_timer->Start();
}

void ResetLapTimer() {
  if (g_lap_timer) {
    g_lap_timer->Reset();
  }
}

void UpdateGps(const minmea_sentence_rmc& rmc) {
  if (g_lap_timer) {
    g_lap_timer->UpdateGps(rmc);
  }
}

}  // namespace app
