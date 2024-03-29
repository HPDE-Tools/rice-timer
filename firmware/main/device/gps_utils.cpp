// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/gps_utils.hpp"

#include <array>
#include <cstdint>

#include "esp_err.h"

#include "common/macros.hpp"
#include "common/utils.hpp"

ParsedNmea ParseNmea(const std::string& line) {
  ParsedNmea parsed{ESP_ERR_INVALID_RESPONSE};
  if (line.empty()) {
    return parsed;
  }
  switch (minmea_sentence_id(line.c_str(), /*strict*/ true)) {
    case MINMEA_SENTENCE_RMC: {
      if (!minmea_parse_rmc(&parsed.emplace<minmea_sentence_rmc>(), line.c_str())) {
        parsed = ESP_ERR_INVALID_RESPONSE;
      }
    } break;
    case MINMEA_SENTENCE_GGA: {
      if (!minmea_parse_gga(&parsed.emplace<minmea_sentence_gga>(), line.c_str())) {
        parsed = ESP_ERR_INVALID_RESPONSE;
      }
    } break;
    case MINMEA_SENTENCE_GST: {
      if (!minmea_parse_gst(&parsed.emplace<minmea_sentence_gst>(), line.c_str())) {
        parsed = ESP_ERR_INVALID_RESPONSE;
      }
    } break;
    case MINMEA_SENTENCE_ZDA: {
      if (!minmea_parse_zda(&parsed.emplace<minmea_sentence_zda>(), line.c_str())) {
        parsed = ESP_ERR_INVALID_RESPONSE;
      }
    } break;
    case MINMEA_UNKNOWN: {
      parsed = ESP_ERR_NOT_SUPPORTED;
    } break;
    default: {
      parsed = ESP_ERR_INVALID_RESPONSE;
    } break;
  }
  return parsed;
}

esp_err_t SendNmea(uart_port_t uart_num, const std::string_view payload) {
  uint8_t checksum = 0;
  for (char c : payload) {
    checksum ^= c;
  }
  if (uart_write_bytes(uart_num, "$", 1) != 1) {
    return ESP_FAIL;
  }
  if (uart_write_bytes(uart_num, payload.data(), payload.size()) != payload.size()) {
    return ESP_FAIL;
  }
  const std::array suffix{
      '*',
      HexDigitUpper((checksum >> 4) & 0xf),
      HexDigitUpper(checksum & 0xf),
      '\r',
      '\n',
  };
  if (uart_write_bytes(uart_num, suffix.data(), suffix.size()) != suffix.size()) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

std::optional<TimeUnixWithUs> GetTimestampFromMinmeaDateTime(
    const minmea_date& date, const minmea_time& time) {
  timespec ts{};
  if (minmea_gettime(&ts, &date, &time) == 0) {
    return ToUnix(ts);
  }
  return {};
}

std::optional<TimeUnixWithUs> GetTimeFromNmea(const ParsedNmea& nmea) {
  minmea_date date;
  minmea_time time;
  const bool matched = std::visit(
      overloaded{
          [&](const minmea_sentence_rmc& rmc) {
            date = rmc.date;
            time = rmc.time;
            return true;
          },
          [&](const minmea_sentence_zda& zda) {
            date = zda.date;
            time = zda.time;
            return true;
          },
          [](const auto&) { return false; }},
      nmea);
  if (!matched) {
    return std::nullopt;
  }
  return GetTimestampFromMinmeaDateTime(date, time);
}

std::optional<minmea_time> GetTimeOfDayFromNmea(const ParsedNmea& nmea) {
  std::optional<minmea_time> result{};
  std::visit(
      overloaded{
          [&](const minmea_sentence_rmc& rmc) { result = rmc.time; },
          [&](const minmea_sentence_gga& gga) { result = gga.time; },
          [&](const minmea_sentence_gst& gst) { result = gst.time; },
          [&](const minmea_sentence_zda& zda) { result = zda.time; },
          [](const auto&) {}},
      nmea);
  return result;
}
