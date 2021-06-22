// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <atomic>
#include <cstdint>
#include <ctime>
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
    float latitude;
    float longitude;
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
  std::optional<Imu> imu{};

  struct Logger {
    int64_t session_id = 0;
    int32_t split_id = 0;
    int32_t lines = 0;
  };
  std::optional<Logger> logger{};

  struct Counter {
    std::atomic<int> gps{};
    std::atomic<int> imu{};
    std::atomic<int> can{};
  };
  Counter counter{};

  std::optional<uint32_t> pps_capture{};

  std::optional<int64_t> lap_start_time_ms = {};
  int32_t num_laps = 0;
  float ltm_x;
  float ltm_y;
};

extern Model g_model;

}  // namespace ui
