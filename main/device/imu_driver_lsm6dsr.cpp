#include "device/imu_driver_lsm6dsr.hpp"

#include <optional>

#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "capture_manager.hpp"
#include "common/logging.hpp"
#include "common/scope_guard.hpp"
#include "logger.hpp"

namespace {
constexpr char TAG[] = "imu_lsm6";
}

spi_device_handle_t g_imu_handle;
xQueueHandle g_imu_queue;
Lsm6dsrConfig g_config;

void HandleImuInterrupt(
    mcpwm_unit_t /*unit*/, mcpwm_capture_signal_t /*signal*/, uint32_t /*edge*/, uint32_t value);

esp_err_t SetupLsm6dsrImu(Lsm6dsrConfig config) {
  g_config = config;
  spi_bus_config_t spi_bus_config = {
      .mosi_io_num = config.mosi_pin,
      .miso_io_num = config.miso_pin,
      .sclk_io_num = config.sclk_pin,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 0,
      .flags = 0,
      .intr_flags = 0,
  };
  TRY(spi_bus_initialize(config.spi, &spi_bus_config, /*dma*/ 0));
  spi_device_interface_config_t spi_device_config = {
      .command_bits = 0,
      .address_bits = 8,
      .dummy_bits = 0,
      .mode = 3,
      .duty_cycle_pos = 128,
      .cs_ena_pretrans = 1,
      .cs_ena_posttrans = 1,
      .clock_speed_hz = 1'000'000,
      .input_delay_ns = 0,
      .spics_io_num = config.cs_pin,
      .flags = SPI_DEVICE_HALFDUPLEX,
      .queue_size = 16,
      .pre_cb = nullptr,
      .post_cb = nullptr,
  };
  TRY(spi_bus_add_device(config.spi, &spi_device_config, &g_imu_handle));

  auto manager = CaptureManager::GetInstance(MCPWM_UNIT_0);
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_1, config.int1_pin));
  TRY(manager->Enable());
  auto channel = manager->GetChannel(MCPWM_SELECT_CAP1);
  channel.Subscribe(MCPWM_POS_EDGE, 0, HandleImuInterrupt);

  g_imu_queue = xQueueCreate(16, sizeof(uint32_t));
  return ESP_OK;
}

void HandleImuInterrupt(
    mcpwm_unit_t /*unit*/, mcpwm_capture_signal_t /*signal*/, uint32_t /*edge*/, uint32_t value) {
  gpio_set_level(GPIO_NUM_13, 1);
  xQueueSendToBackFromISR(g_imu_queue, &value, nullptr);
}

#define READ 0x80
#define WRITE 0x00
#define WHO_AM_I 0x0F
#define WHO_AM_I_EXPECTED 0x6B
#define CTRL1_XL 0x10
#define CTRL2_G 0x11
#define INT1_CTRL 0x0D
#define STATUS_REG 0x1E

std::optional<uint8_t> ReadOneReg(uint8_t reg) {
  spi_transaction_t txn{};
  txn.flags = SPI_TRANS_USE_RXDATA;
  txn.addr = READ | reg;
  txn.length = 0;
  txn.rxlength = 8;
  OK_OR_RETURN(spi_device_polling_transmit(g_imu_handle, &txn), std::nullopt);
  return txn.rx_data[0];
}

esp_err_t WriteOneReg(uint8_t reg, uint8_t value) {
  spi_transaction_t txn{};
  txn.flags = SPI_TRANS_USE_TXDATA;
  txn.addr = WRITE | reg;
  txn.length = 8;
  txn.rxlength = 0;
  txn.tx_data[0] = value;
  TRY(spi_device_polling_transmit(g_imu_handle, &txn));
  return ESP_OK;
}

esp_err_t TestImu() {
  TRY(spi_device_acquire_bus(g_imu_handle, portMAX_DELAY));
  SCOPE_EXIT { spi_device_release_bus(g_imu_handle); };

  const auto who_am_i = ReadOneReg(WHO_AM_I);
  CHECK(who_am_i);
  if (*who_am_i != WHO_AM_I_EXPECTED) {
    ESP_LOGE(TAG, "who am i => %02X (should be %02X)", *who_am_i, WHO_AM_I_EXPECTED);
    return ESP_ERR_INVALID_RESPONSE;
  }
  TRY(WriteOneReg(INT1_CTRL, 0b00000011));  // INT1_DRDY_G, INT1_DRDY_XL
  TRY(WriteOneReg(CTRL1_XL, 0b00010000));   // 12.5 Hz, 2g
  TRY(WriteOneReg(CTRL2_G, 0b00010000));    // 12.5 Hz, 250 dps
  while (true) {
    uint32_t capture = 0;
    if (gpio_get_level(g_config.int1_pin) == 0) {
      if (xQueueReceive(g_imu_queue, &capture, portMAX_DELAY) != pdPASS) {
        ESP_LOGE(TAG, "timeout waiting for interrupt");
        continue;
      }
    }
    gpio_set_level(GPIO_NUM_13, 0);
    const auto status_reg = ReadOneReg(STATUS_REG);
    if (!status_reg) {
      ESP_LOGE(TAG, "cannot get status reg");
      vTaskDelay(1);
      continue;
    }
    if (status_reg != 0x07) {
      vTaskDelay(1);
      continue;
    }
    {
      spi_transaction_t txn{};
      txn.flags = 0;
      txn.addr = READ | 0x20;
      txn.length = 0;
      txn.rxlength = 8 * 14;
      static char rx_buf[14] = {};
      txn.rx_buffer = rx_buf;
      TRY(spi_device_transmit(g_imu_handle, &txn));
      const uint16_t temp = (uint16_t{rx_buf[1]} << 8) | rx_buf[0];
      const int16_t gx = (uint16_t{rx_buf[3]} << 8) | rx_buf[2];
      const int16_t gy = (uint16_t{rx_buf[5]} << 8) | rx_buf[4];
      const int16_t gz = (uint16_t{rx_buf[7]} << 8) | rx_buf[5];
      const int16_t ax = (uint16_t{rx_buf[9]} << 8) | rx_buf[8];
      const int16_t ay = (uint16_t{rx_buf[11]} << 8) | rx_buf[10];
      const int16_t az = (uint16_t{rx_buf[13]} << 8) | rx_buf[12];
      (void)temp;
      std::string line = fmt::format(
          "i,{},{:+06d},{:+06d},{:+06d},{:+06d},{:+06d},{:+06d}", capture, ax, ay, az, gx, gy, gz);
      ESP_LOGI(TAG, "%s", line.c_str());
      SendToLogger(std::move(line));
    }
  }
  return ESP_OK;
}
