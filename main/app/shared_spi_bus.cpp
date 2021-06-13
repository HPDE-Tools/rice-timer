// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/shared_spi_bus.hpp"

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "sdkconfig.h"

#include "common/logging.hpp"

namespace app {

esp_err_t SetupSharedSpiBus() {
  static bool configured = false;
  if (configured) {
    return ESP_OK;
  }
  spi_bus_config_t bus_config;
  if constexpr (CONFIG_HW_VERSION == 1) {
    bus_config = {
        .mosi_io_num = GPIO_NUM_25,
        .miso_io_num = GPIO_NUM_39,
        .sclk_io_num = GPIO_NUM_26,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
        .flags = 0,
        .intr_flags = 0,
    };
  } else if constexpr (CONFIG_HW_VERSION == 2) {
    bus_config = {
        .mosi_io_num = GPIO_NUM_23,
        .miso_io_num = GPIO_NUM_19,
        .sclk_io_num = GPIO_NUM_18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
        .flags = 0,
        .intr_flags = 0,
    };
  } else if constexpr (CONFIG_HW_VERSION == 3) {
    bus_config = {
        .mosi_io_num = GPIO_NUM_23,
        .miso_io_num = GPIO_NUM_NC,
        .sclk_io_num = GPIO_NUM_18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
        .flags = 0,
        .intr_flags = 0,
    };
  } else {
    return ESP_FAIL;
  }
  TRY(spi_bus_initialize(VSPI_HOST, &bus_config, /*dma*/ VSPI_HOST));
  configured = true;
  return ESP_OK;
}

}  // namespace app
