// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/display.hpp"

#include "driver/spi_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "app/shared_spi_bus.hpp"
#include "common/macros.hpp"
#include "common/times.hpp"

namespace ui {

std::unique_ptr<OledSsd1309> g_oled;

esp_err_t SetupOled() {
  TRY(app::SetupSharedSpiBus());

  gpio_num_t cs_pin = GPIO_NUM_NC;
  gpio_num_t dc_pin = GPIO_NUM_NC;
  if constexpr (CONFIG_HW_VERSION == 3) {
    cs_pin = GPIO_NUM_5;
    dc_pin = GPIO_NUM_19;
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }

  g_oled = OledSsd1309::Create(OledSsd1309::Option{
      .spi = VSPI_HOST,
      .cs_pin = cs_pin,
      .dc_pin = dc_pin,
  });
  if (!g_oled) {
    return ESP_FAIL;
  }
  TRY(g_oled->Flush());

  return ESP_OK;
}

}  // namespace ui
