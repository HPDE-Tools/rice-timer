#pragma once

#include <cstdint>
#include <ctime>
#include <optional>

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
};

extern Model g_model;

}  // namespace ui
