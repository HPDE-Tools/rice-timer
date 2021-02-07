// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/imu_instance.hpp"

#include "common/logging.hpp"
#include "priorities.hpp"

namespace app {

std::unique_ptr<Lsm6dsr> g_imu{};

esp_err_t SetupImu() {
  gpio_num_t cs_pin;
  gpio_num_t interrupt_pin;
  spi_bus_config_t bus_config;
  if constexpr (CONFIG_HW_VERSION == 1) {
    gpio_pad_select_gpio(GPIO_NUM_13);
    gpio_set_direction(GPIO_NUM_13, GPIO_MODE_OUTPUT);
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
    cs_pin = GPIO_NUM_21;
    interrupt_pin = GPIO_NUM_34;
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
    cs_pin = GPIO_NUM_5;
    interrupt_pin = GPIO_NUM_22;
  } else {
    return ESP_FAIL;
  }
  TRY(spi_bus_initialize(VSPI_HOST, &bus_config, /*dma*/ 0));
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_1, interrupt_pin));
  g_imu = Lsm6dsr::Create(
      CaptureManager::GetInstance(MCPWM_UNIT_0)->GetChannel(MCPWM_SELECT_CAP1),
      {
          .spi = VSPI_HOST,
          .cs_pin = cs_pin,
          .interrupt_pin = interrupt_pin,
          .accel_output_data_rate = Lsm6dsr::kOdr104Hz,
          .accel_full_scale = Lsm6dsr::kAccelFs2g,
          .gyro_output_data_rate = Lsm6dsr::kOdr104Hz,
          .gyro_full_scale = Lsm6dsr::kGyroFs500Dps,
          .priority = kPriorityImu,
      });
  return g_imu ? ESP_OK : ESP_FAIL;
}

}  // namespace app
