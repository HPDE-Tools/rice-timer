#pragma once

#include <string_view>
#include <variant>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#include "common/times.hpp"
#include "driver/uart.h"

struct GpsTimeFix {
  uint32_t pps_capture;
  TickType_t pps_ostime;
  TickType_t gps_ostime;
  TimeUnix parsed_time_unix;
};

using ParsedNmea =
    std::variant<esp_err_t, minmea_sentence_rmc, minmea_sentence_gga, minmea_sentence_zda>;

ParsedNmea ParseNmea(const std::string& line);

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
