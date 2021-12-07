// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <optional>
#include <string_view>
#include <variant>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "minmea.h"

#include "common/times.hpp"
#include "driver/uart.h"

constexpr int kBuildCentury = ((__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100);
static_assert(kBuildCentury == 2000);  // sure...

struct GpsTimeFix {
  uint32_t pps_capture;
  TickType_t pps_ostime;
  TickType_t gps_ostime;
  TimeUnix parsed_time_unix;
};

using ParsedNmea = std::variant<
    esp_err_t,
    minmea_sentence_rmc,
    minmea_sentence_gga,
    minmea_sentence_gst,
    minmea_sentence_zda>;

constexpr float kKnotInMph = 1.151f;
constexpr float kKnotInKph = 1.852f;

/// Attempt to parse an NMEA sentence
///
/// \returns one of the minmea_sentence_xxx variants, if the line successfully parsed;
///          ESP_ERR_NOT_SUPPORTED, if the line contains valid NMEA that we cannot parse;
///          ESP_ERR_INVALID_RESPONSE, if the line does not contain valid NMEA.
IRAM_ATTR ParsedNmea ParseNmea(const std::string& line);

/// Sends an NMEA sentence, automatically prepending and appending framing and checksum.
///
/// \param uart_num UART port to send to
/// \param payload NMEA sentence between '$' and '*' (excluding both delimiters)
/// \returns ESP_FAIL if failed to write to UART;
///          ESP_OK otherwise.
///
/// \example payload: "GPRMC,whatever,123,456,test"
///          actually sent to UART: "$GPRMC,whatever,123,456,test*54\r\n"
esp_err_t SendNmea(uart_port_t uart_num, const std::string_view payload);

IRAM_ATTR std::optional<TimeUnixWithUs> GetTimestampFromMinmeaDateTime(
    const minmea_date& date, const minmea_time& time);

IRAM_ATTR std::optional<TimeUnixWithUs> GetTimeFromNmea(const ParsedNmea& nmea);

IRAM_ATTR std::optional<minmea_time> GetTimeOfDayFromNmea(const ParsedNmea& nmea);

inline bool operator==(const minmea_time& lhs, const minmea_time& rhs) {
  return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes && lhs.seconds == rhs.seconds &&
         lhs.microseconds == rhs.microseconds;
}
