// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <atomic>
#include <cstdint>
#include <ctime>
#include <limits>
#include <optional>

#include "common/times.hpp"

namespace ui {

struct Model {
  struct Gps {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t millisecond;
    uint8_t num_sats;
    float latitude;
    float longitude;
    float speed_knot;
    float course_deg;
  };
  std::optional<Gps> gps{};

  struct Imu {
    float ax_g;
    float ay_g;
    float az_g;
    float wx_dps;
    float wy_dps;
    float wz_dps;
  };
  struct ImuRaw {
    int ax_raw;
    int ay_raw;
    int az_raw;
    int wx_raw;
    int wy_raw;
    int wz_raw;
  };
  std::optional<Imu> imu{};
  std::optional<ImuRaw> imu_raw{};

  struct Logger {
    int64_t session_id = 0;
    int32_t split_id = 0;
    int32_t lines = 0;
  };
  std::optional<Logger> logger{};
  bool is_logger_running = false;

  struct Counter {
    std::atomic<int> gps{};
    std::atomic<int> imu{};
    std::atomic<int> can{};
  };
  Counter counter{};
  Counter lost{};

  struct SdCard {
    int64_t capacity_bytes;
    int64_t free_bytes;
  };
  std::optional<SdCard> sd_card{};

  std::string map_name;
  struct LapTimer {
    int num_complete_laps = 0;
    std::optional<int64_t> curr_lap_start_timestamp_ms{};
    int64_t min_lap_duration_ms = std::numeric_limits<int64_t>::max();
    int min_lap_index = -1;
    std::optional<int64_t> last_lap_duration_ms{};
  };
  std::optional<LapTimer> lap_timer{};
};

extern Model g_model;

}  // namespace ui
