// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/shared_spi_bus.hpp"

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "sdkconfig.h"

#include "common/macros.hpp"

namespace app {

namespace {
static const char TAG[] = "spi";
}  // namespace

esp_err_t SetupSharedSpiBus() {
  static bool configured = false;
  if (configured) {
    return ESP_OK;
  }

  gpio_num_t sclk_pin = GPIO_NUM_NC;
  gpio_num_t mosi_pin = GPIO_NUM_NC;
  gpio_num_t miso_pin = GPIO_NUM_NC;
  if constexpr (CONFIG_HW_VERSION == 1) {
    mosi_pin = GPIO_NUM_25;
    miso_pin = GPIO_NUM_39;
    sclk_pin = GPIO_NUM_26;
  } else if constexpr (CONFIG_HW_VERSION == 2) {
    mosi_pin = GPIO_NUM_23;
    miso_pin = GPIO_NUM_19;
    sclk_pin = GPIO_NUM_18;
  } else if constexpr (CONFIG_HW_VERSION == 3) {
    mosi_pin = GPIO_NUM_23;
    miso_pin = GPIO_NUM_NC;
    sclk_pin = GPIO_NUM_18;
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }

  spi_bus_config_t bus_config = {
      .mosi_io_num = mosi_pin,
      .miso_io_num = miso_pin,
      .sclk_io_num = sclk_pin,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 0,
      .flags = 0,
      .intr_flags = 0,
  };
  TRY(spi_bus_initialize(VSPI_HOST, &bus_config, /*dma*/ VSPI_HOST));
  configured = true;
  return ESP_OK;
}

}  // namespace app
