// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/oled_instance.hpp"

#include "driver/spi_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app/shared_spi_bus.hpp"
#include "common/logging.hpp"
#include "common/times.hpp"

namespace app {

std::unique_ptr<OledSsd1309> g_oled;

esp_err_t SetupOled() {
  TRY(SetupSharedSpiBus());
  gpio_num_t cs_pin = GPIO_NUM_NC;
  gpio_num_t dc_pin = GPIO_NUM_NC;
  if constexpr (CONFIG_HW_VERSION == 3) {
    cs_pin = GPIO_NUM_5;
    dc_pin = GPIO_NUM_19;
  } else {
    return ESP_FAIL;
  }

  g_oled = OledSsd1309::Create(OledSsd1309::Option{
      .spi = VSPI_HOST,
      .cs_pin = cs_pin,
      .dc_pin = dc_pin,
  });
  if (!g_oled) {
    return ESP_FAIL;
  }
  vTaskDelay(pdMS_TO_TICKS(100));
  TRY(g_oled->SetDisplayEnabled(true));
  return ESP_OK;
}

}  // namespace app
