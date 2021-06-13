// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/can_instance.hpp"

#include "device/can.hpp"
#include "priorities.hpp"

namespace app {

namespace {}  // namespace

std::unique_ptr<CanManager> g_can;

esp_err_t SetupCan() {
  g_can = CanManager::Create({
#if CONFIG_HW_VERSION == 1
    .tx_pin = GPIO_NUM_12, .rx_pin = GPIO_NUM_27,
#elif CONFIG_HW_VERSION == 2
    .tx_pin = GPIO_NUM_33, .rx_pin = GPIO_NUM_32,
#elif CONFIG_HW_VERSION == 3
    .tx_pin = GPIO_NUM_32, .rx_pin = GPIO_NUM_35,
#endif
    .priority = kPriorityCan,
  });
  return g_can ? ESP_OK : ESP_FAIL;
}

}  // namespace app
