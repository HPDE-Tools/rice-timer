#pragma once

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "esp_err.h"

struct Lsm6dsrConfig {
  spi_host_device_t spi;
  gpio_num_t mosi_pin;
  gpio_num_t miso_pin;
  gpio_num_t sclk_pin;
  gpio_num_t cs_pin;
  gpio_num_t int1_pin;
};

extern spi_device_handle_t g_imu_handle;

esp_err_t SetupLsm6dsrImu(Lsm6dsrConfig config);

esp_err_t TestImu();
