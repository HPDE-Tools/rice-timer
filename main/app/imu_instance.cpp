// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/imu_instance.hpp"

#include "app/shared_spi_bus.hpp"
#include "common/macros.hpp"
#include "priorities.hpp"

namespace app {

std::unique_ptr<Lsm6dsr> g_imu{};

esp_err_t SetupImu() {
  TRY(SetupSharedSpiBus());
  gpio_num_t cs_pin = GPIO_NUM_NC;
  gpio_num_t interrupt_pin = GPIO_NUM_NC;
  if constexpr (CONFIG_HW_VERSION == 1) {
    // DEBUG: measure interrupt handling latency and task handling latency
    gpio_pad_select_gpio(GPIO_NUM_13);
    gpio_set_direction(GPIO_NUM_13, GPIO_MODE_OUTPUT);

    cs_pin = GPIO_NUM_21;
    interrupt_pin = GPIO_NUM_34;
  } else if constexpr (CONFIG_HW_VERSION == 2) {
    cs_pin = GPIO_NUM_5;
    interrupt_pin = GPIO_NUM_22;
  } else if constexpr (CONFIG_HW_VERSION == 3) {
    cs_pin = GPIO_NUM_33;
    interrupt_pin = GPIO_NUM_39;  // SENSOR_VN
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_1, interrupt_pin));
  g_imu = Lsm6dsr::Create(
      CaptureManager::GetInstance(MCPWM_UNIT_0)->GetChannel(MCPWM_SELECT_CAP1),
      Lsm6dsr::Option{
          .spi = VSPI_HOST,
          .cs_pin = cs_pin,
          .interrupt_pin = interrupt_pin,
          .spi_three_wire = true,
          .accel_output_data_rate = Lsm6dsr::kOdr104Hz,
          .accel_full_scale = Lsm6dsr::kAccelFs2g,
          .gyro_output_data_rate = Lsm6dsr::kOdr104Hz,
          .gyro_full_scale = Lsm6dsr::kGyroFs500Dps,
          .priority = kPriorityImu,
      });
  return g_imu ? ESP_OK : ESP_FAIL;
}

}  // namespace app
