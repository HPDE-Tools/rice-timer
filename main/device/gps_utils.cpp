#include "device/gps_utils.hpp"

#include <array>
#include <cstdint>

#include "esp_err.h"

#include "common/utils.hpp"

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
