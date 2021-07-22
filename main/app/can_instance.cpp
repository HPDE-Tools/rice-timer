// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/can_instance.hpp"

#include <charconv>

#include "app/logger_instance.hpp"
#include "common/utils.hpp"
#include "device/can.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "app/can";

IRAM_ATTR char* WriteHexUpper(char* s, uint32_t value, int len) {
  for (char* p = s + len - 1; p >= s; --p, value >>= 4) {
    *p = HexDigitUpper(value & 0xf);
  }
  return s + len;
}

IRAM_ATTR void HandleCanMessage(uint32_t current_capture, twai_message_t message) {
  static char buf[] = "c,2147483647,b0b1b2b3,8,d0d1d2d3d4d5d6d7";
  char* const buf_begin = buf + 2;
  char* const buf_end = buf + sizeof(buf);

  const uint8_t dlc = std::min(message.data_length_code, uint8_t{8});

  char* p = buf_begin;
  p = std::to_chars(p, buf_end, current_capture, /*base*/ 10).ptr;
  *p++ = ',';
  p = WriteHexUpper(p, message.identifier, message.extd ? 8 : 3);
  *p++ = ',';
  *p++ = '0' + dlc;
  *p++ = ',';
  for (int i = 0; i < dlc; i++) {
    p = WriteHexUpper(p, message.data[i], 2);
  }
  *p++ = '\0';
  CHECK(p < buf_end);

  const esp_err_t err = SendToLogger(app::kCanProducer, std::string_view(buf, p - buf - 1));
  if (err == ESP_FAIL) {
    ++ui::g_model.lost.can;
  }
  ++ui::g_model.counter.can;
}

}  // namespace

std::unique_ptr<CanManager> g_can{};

esp_err_t SetupCan() {
  gpio_num_t tx_pin = GPIO_NUM_NC;
  gpio_num_t rx_pin = GPIO_NUM_NC;
  if constexpr (CONFIG_HW_VERSION == 1) {
    tx_pin = GPIO_NUM_12;
    rx_pin = GPIO_NUM_27;
  } else if constexpr (CONFIG_HW_VERSION == 2) {
    tx_pin = GPIO_NUM_33;
    rx_pin = GPIO_NUM_32;
  } else if constexpr (CONFIG_HW_VERSION == 3) {
    tx_pin = GPIO_NUM_32;
    rx_pin = GPIO_NUM_35;
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }
  // TODO(summivox): configurable CAN baud rate
  g_can = CanManager::Create(CanManager::Option{
      .tx_pin = tx_pin,
      .rx_pin = rx_pin,
      .tx_queue_len = 8,
      .rx_queue_len = 1024,
      .timing = CalculateCanTiming(500'000, 15, 4, 3, false),

      .priority = kPriorityCan,
  });
  return g_can ? ESP_OK : ESP_FAIL;
}

esp_err_t StartCanInstance() {
  if (!g_can) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_can->Start(HandleCanMessage);
}

}  // namespace app
