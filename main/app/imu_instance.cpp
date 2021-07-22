// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/imu_instance.hpp"

#include <charconv>

#include "app/logger_instance.hpp"
#include "app/shared_spi_bus.hpp"
#include "common/macros.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "app/imu";

IRAM_ATTR void HandleImuRawData(const Lsm6dsr::RawImuData& data) {
#if 1
  ui::g_model.imu = ui::Model::Imu{
      .ax_g = app::g_imu->AccelRawToG(data.ax),
      .ay_g = app::g_imu->AccelRawToG(data.ay),
      .az_g = app::g_imu->AccelRawToG(data.az),
      .wx_dps = app::g_imu->GyroRawToDps(data.wx),
      .wy_dps = app::g_imu->GyroRawToDps(data.wy),
      .wz_dps = app::g_imu->GyroRawToDps(data.wz),
  };
#else
  ui::g_model.imu_raw = ui::Model::ImuRaw{
      .ax_raw = data.ax,
      .ay_raw = data.ay,
      .az_raw = data.az,
      .wx_raw = data.wx,
      .wy_raw = data.wy,
      .wz_raw = data.wz,
  };
#endif
  ++ui::g_model.counter.imu;
  static char buf[] = "i,2147483647,-32768,-32768,-32768,-32768,-32768,-32768";
  char* const buf_begin = buf + 2;
  char* const buf_end = buf + sizeof(buf);
  char* p = buf_begin;
  p = std::to_chars(p, buf_end, data.capture, /*base*/ 10).ptr;
  *p++ = ',';
  p = std::to_chars(p, buf_end, data.ax, /*base*/ 10).ptr;
  *p++ = ',';
  p = std::to_chars(p, buf_end, data.ay, /*base*/ 10).ptr;
  *p++ = ',';
  p = std::to_chars(p, buf_end, data.az, /*base*/ 10).ptr;
  *p++ = ',';
  p = std::to_chars(p, buf_end, data.wx, /*base*/ 10).ptr;
  *p++ = ',';
  p = std::to_chars(p, buf_end, data.wy, /*base*/ 10).ptr;
  *p++ = ',';
  p = std::to_chars(p, buf_end, data.wz, /*base*/ 10).ptr;
  *p++ = '\0';
  CHECK(p < buf_end);
  const esp_err_t err = SendToLogger(app::kImuProducer, std::string_view(buf, p - buf - 1));
  if (err == ESP_FAIL) {
    ++ui::g_model.lost.imu;
  }
}

}  // namespace

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

esp_err_t StartImuInstance() {
  if (!g_imu) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_imu->Start(HandleImuRawData);
}

}  // namespace app
