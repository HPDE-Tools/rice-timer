// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/gps_driver_mtk.hpp"

#include <cinttypes>
#include <cstdint>
#include <optional>

#include "fmt/core.h"
#include "scope_guard/scope_guard.hpp"

#include "common/logging.hpp"
#include "device/gps_utils.hpp"
#include "io/autobaud.hpp"

namespace {

constexpr char TAG[] = "gps_mtk";

constexpr uint32_t kGpsDetectTimeoutMs = 5000;
constexpr uint32_t kGpsRetryMs = 1000;

constexpr size_t kGpsDefaultBaud = 9600;
// accepted actual baud range: [desired - desired / tol, desired + desired / tol]
constexpr int kGpsBaudRelativeTolerance = 30;

}  // namespace

esp_err_t SetupMtkGps(
    uart_port_t uart_num,
    uart_dev_t* uart_dev,
    io::UartLineReader* line_reader,
    int desired_baud,
    int desired_output_period_ms) {
  while (true) {
    SCOPE_EXIT { vTaskDelay(pdMS_TO_TICKS(kGpsRetryMs)); };

    ESP_LOGI(TAG, "Detecting baud rate");
    std::optional<int32_t> bit_width =
        io::DetectUartBitWidth(uart_dev, {.timeout = kGpsDetectTimeoutMs});
    if (!bit_width) {
      ESP_LOGW(TAG, "Baud rate detection fail");
      continue;
    }
    io::SetUartBitWidth(uart_dev, *bit_width);
    std::optional<uint32_t> current_baud = io::GetCurrentUartBaudRate(uart_num);
    if (!current_baud) {
      ESP_LOGW(TAG, "Failed to get current baud rate");
      continue;
    }
    ESP_LOGI(TAG, "Baud rate set to %" PRIu32, *current_baud);

    if (line_reader->ReadOneLine(kGpsDetectTimeoutMs).empty()) {
      ESP_LOGW(TAG, "Did not receive line from GPS");
      continue;
    }
    const int tol = desired_baud / kGpsBaudRelativeTolerance;
    if (!(desired_baud - tol <= *current_baud && *current_baud <= desired_baud + tol)) {
      ESP_LOGI(TAG, "Attempt to change baud to %" PRIu32, desired_baud);
      TRY(SendNmea(uart_num, fmt::format("PMTK251,{}", desired_baud)));
      continue;
    }

    break;
  }

  // configure output rate and type
  TRY(SendNmea(uart_num, fmt::format("PMTK220,{}", desired_output_period_ms)));
  TRY(SendNmea(uart_num, "PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0"));  // GPRMC, GPGGA

  return ESP_OK;
}
