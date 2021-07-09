// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/can_instance.hpp"

#include "device/can.hpp"
#include "priorities.hpp"

namespace app {

namespace {}  // namespace

std::unique_ptr<CanManager> g_can;

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

}  // namespace app
