// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/shared_spi_bus.hpp"

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#include "common/logging.hpp"

namespace app {

namespace {
constexpr char TAG[] = "i2c";

constexpr int kI2cClockSpeed = 486'912;           // NOTE: ~400 kbit/s after ESP32 distortion (?)
constexpr int kI2cTimeout = APB_CLK_FREQ * 1e-3;  // 1ms timeout tolerance
}  // namespace

esp_err_t SetupSharedI2cBus() {
  static bool configured = false;
  if (configured) {
    return ESP_OK;
  }

  const i2c_port_t port = I2C_NUM_0;
  gpio_num_t scl_pin = GPIO_NUM_NC;
  gpio_num_t sda_pin = GPIO_NUM_NC;
  if constexpr (CONFIG_HW_VERSION == 1) {
    scl_pin = GPIO_NUM_22;
    sda_pin = GPIO_NUM_23;
  } else if constexpr (CONFIG_HW_VERSION == 2) {
    scl_pin = GPIO_NUM_26;
    sda_pin = GPIO_NUM_25;
  } else if constexpr (CONFIG_HW_VERSION == 3) {
    scl_pin = GPIO_NUM_17;
    sda_pin = GPIO_NUM_16;
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }

  i2c_config_t conf = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = sda_pin,
      .scl_io_num = scl_pin,
      .sda_pullup_en = false,  // all pullups are external
      .scl_pullup_en = false,
      .master =
          {
              .clk_speed = kI2cClockSpeed,
          },
      .clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL,
  };

  // TRY(i2c_param_config(port, &conf));
  // TRY(i2c_set_timeout(port, kI2cTimeout));
  // TRY(i2c_driver_install(port, I2C_MODE_MASTER, /*rx buf*/ 0, /*tx buf*/ 0, /*flags*/ 0));
  return ESP_OK;
}

}  // namespace app
