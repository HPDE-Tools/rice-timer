// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <ctime>
#include <optional>

#include "common/times.hpp"

namespace ui {

struct Model {
  struct Gps {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t millisecond;
    float latitude;
    float longitude;
  };

  struct Imu {
    float ax;
    float ay;
    float az;
  };

  std::optional<uint32_t> pps_capture = {};
  std::optional<Gps> gps = {};
  std::optional<Imu> imu = {};

  int32_t logger_session_id = 0;
  int32_t logger_split_id = 0;
  int32_t logger_lines = 0;

  std::optional<int64_t> lap_start_time_ms = {};
  int32_t num_laps = 0;
};

extern Model g_model;

}  // namespace ui
