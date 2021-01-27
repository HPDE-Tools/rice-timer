#include "io/autobaud.hpp"

#include <algorithm>
#include <cmath>

#include "esp32/clk.h"
#include "freertos/task.h"

#include "common/logging.hpp"

namespace io {

namespace {

constexpr char TAG[] = "autobaud";

std::optional<int32_t> InferBitWidth(uint32_t a, uint32_t b) {
  const int l = std::min(a, b);
  const int h = std::max(a, b);
  const int tol = l / 10;
  for (int mul = 1; mul <= 9; mul++) {
    if (std::abs(h - l * mul) < tol) {
      return (l + h / mul) / 2;
    }
  }
  return std::nullopt;
}

}  // namespace

std::optional<int32_t> DetectUartBitWidth(uart_dev_t* uart, const UartAutoBaudOption& option) {
  CHECK(uart != nullptr);

  uart->auto_baud.en = 0;
  uart->auto_baud.glitch_filt = option.glitch_filter;
  uart->auto_baud.en = 1;

  const TickType_t start_time_ticks = xTaskGetTickCount();
  while (uart->rxd_cnt.edge_cnt < option.min_num_edges &&
         static_cast<int>(xTaskGetTickCount() - start_time_ticks) < option.timeout) {
    vTaskDelay(option.poll_interval);
  }

  if (uart->rxd_cnt.edge_cnt < option.min_num_edges) {
    ESP_LOGW(TAG, "timeout");
    uart->auto_baud.en = 0;
    return std::nullopt;
  }
  const uint32_t edge_cnt = uart->rxd_cnt.edge_cnt;
  const uint32_t low_duration = uart->lowpulse.min_cnt;
  const uint32_t high_duration = uart->highpulse.min_cnt;
  const uint32_t rising_count = uart->pospulse.min_cnt;
  const uint32_t falling_count = uart->negpulse.min_cnt;
  uart->auto_baud.en = 0;

  ESP_LOGV(TAG, "low duration: %d, high duration: %d", low_duration, high_duration);
  ESP_LOGV(
      TAG,
      "rising count: %d, falling count: %d, rxd_cnt: %d",
      rising_count,
      falling_count,
      edge_cnt);

  return InferBitWidth(low_duration, high_duration);
}

std::optional<int32_t> DetectUartBaudRate(uart_dev_t* uart, const UartAutoBaudOption& option) {
  const std::optional<int32_t> bit_width = DetectUartBitWidth(uart, option);
  if (!bit_width) {
    return std::nullopt;
  }
  const int apb_freq = esp_clk_apb_freq();
  ESP_LOGV(TAG, "apb freq: %d", apb_freq);
  return apb_freq / (*bit_width);
}

void SetUartBitWidth(uart_dev_t* UART, int32_t bit_width) {
  UART->clk_div.div_int = bit_width;
  UART->clk_div.div_frag = 0;
}

}  // namespace io
