// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/imu_driver_lsm6dsr.hpp"

#include <optional>
#include <string_view>

#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "common/logging.hpp"
#include "common/scope_guard.hpp"
#include "common/utils.hpp"
#include "device/capture_manager.hpp"

namespace {
constexpr char TAG[] = "imu_lsm6dsr";

constexpr int kImuStackSize = 4096;
constexpr int kImuPollPeriodMs = 1;

constexpr uint8_t kRead = 0x80;
constexpr uint8_t kWrite = 0x00;

constexpr uint8_t kSpiThreeWire = 0b00001100;  // CTRL3_C: SIM | IF_INC
constexpr uint8_t kChipSelfId = 0x6B;

std::optional<uint8_t> ReadOneReg(spi_device_handle_t spi, uint8_t reg) {
  spi_transaction_t txn{};
  txn.flags = SPI_TRANS_USE_RXDATA;
  txn.addr = kRead | reg;
  txn.length = 0;
  txn.rxlength = 8;
  OK_OR_RETURN(spi_device_polling_transmit(spi, &txn), std::nullopt);
  return txn.rx_data[0];
}

esp_err_t WriteOneReg(spi_device_handle_t spi, uint8_t reg, uint8_t value) {
  spi_transaction_t txn{};
  txn.flags = SPI_TRANS_USE_TXDATA;
  txn.addr = kWrite | reg;
  txn.length = 8;
  txn.rxlength = 0;
  txn.tx_data[0] = value;
  TRY(spi_device_polling_transmit(spi, &txn));
  return ESP_OK;
}

esp_err_t ReadRegs(spi_device_handle_t spi, uint8_t reg_start, uint8_t len, uint8_t* out_buf) {
  spi_transaction_t txn{};
  txn.flags = 0;
  txn.addr = kRead | reg_start;
  txn.length = 0;
  txn.rxlength = 8 * len;
  txn.rx_buffer = out_buf;
  TRY(spi_device_transmit(spi, &txn));
  return ESP_OK;
}

}  // namespace

Lsm6dsr::Lsm6dsr(CaptureChannel interrupt_capture, Option option)
    : option_(option), capture_(interrupt_capture) {}

Lsm6dsr::~Lsm6dsr() { Teardown(); }

esp_err_t Lsm6dsr::Setup() {
  spi_device_interface_config_t spi_device_config = {
      .command_bits = 0,
      .address_bits = 8,
      .dummy_bits = 0,
      .mode = 3,
      .duty_cycle_pos = 128,
      .cs_ena_pretrans = 1,
      .cs_ena_posttrans = 1,
      .clock_speed_hz = 10'000'000,  // because we can
      .input_delay_ns = 0,
      .spics_io_num = option_.cs_pin,
      .flags = SPI_DEVICE_HALFDUPLEX | (option_.spi_three_wire ? SPI_DEVICE_3WIRE : 0u),
      .queue_size = 16,
      .pre_cb = nullptr,
      .post_cb = nullptr,
  };
  TRY(spi_bus_add_device(option_.spi, &spi_device_config, &spi_device_));

  if (option_.spi_three_wire) {
    // set 3-wire half duplex flag first (otherwise we can't read)
    TRY(WriteOneReg(spi_device_, Reg::CTRL3_C, kSpiThreeWire));
  }

  // read and validate chip self-ID register
  const std::optional<uint8_t> who_am_i = ReadOneReg(spi_device_, Reg::WHO_AM_I);
  if (!who_am_i || *who_am_i != kChipSelfId) {
    ESP_LOGE(
        TAG,
        "chip self id (reg %02X) => %02X (should be %02X)",
        Reg::WHO_AM_I,
        *who_am_i,
        kChipSelfId);
    return ESP_ERR_INVALID_RESPONSE;
  }

  // configure the outputs
  TRY(WriteOneReg(spi_device_, Reg::INT1_CTRL, 0b00000011));  // INT1_DRDY_G, INT1_DRDY_XL
  TRY(WriteOneReg(
      spi_device_,
      Reg::CTRL1_XL,
      (option_.accel_output_data_rate << 4) | (option_.accel_full_scale << 2)));
  TRY(WriteOneReg(
      spi_device_,
      Reg::CTRL2_G,
      (option_.gyro_output_data_rate << 4) | (option_.gyro_full_scale << 0)));

  return ESP_OK;
}

void Lsm6dsr::Teardown() {
  Stop();
  spi_bus_remove_device(spi_device_);
}

esp_err_t Lsm6dsr::Start(RawImuDataSubscriber callback) {
  subscriber_ = callback;
  TRY(Task::SpawnSame(TAG, kImuStackSize, option_.priority));
  const TaskHandle_t handle = Task::handle();
  TRY(capture_.Subscribe(
      MCPWM_POS_EDGE,
      0,
      [handle](
          mcpwm_unit_t /*unit*/,
          mcpwm_capture_signal_t /*signal*/,
          uint32_t /*edge*/,
          uint32_t value) {
        xTaskNotifyFromISR(handle, value, eSetValueWithOverwrite, nullptr);
        if constexpr (CONFIG_HW_VERSION == 1) {
          // DEBUG: measure interrupt handling latency and task handling latency
          gpio_set_level(GPIO_NUM_13, 1);
        }
      }));
  return ESP_OK;
}

void Lsm6dsr::Stop() {
  capture_.Unsubscribe();
  Task::Kill();
}

void Lsm6dsr::Run() {
  static uint8_t buf[14];
  static RawImuData data;
  while (true) {
    uint32_t capture = 0;
    if (gpio_get_level(option_.interrupt_pin) == 1) {
      capture_.TriggerNow();
    }
    if (xTaskNotifyWait(0, 0, &capture, pdMS_TO_TICKS(kImuPollPeriodMs)) != pdPASS) {
      continue;
    }

    if constexpr (CONFIG_HW_VERSION == 1) {
      // DEBUG: measure interrupt handling latency and task handling latency
      gpio_set_level(GPIO_NUM_13, 0);
    }

    if (spi_device_acquire_bus(spi_device_, portMAX_DELAY) != ESP_OK) {
      ESP_LOGW(TAG, "failed to acquire SPI bus");
      continue;
    }
    SCOPE_EXIT { spi_device_release_bus(spi_device_); };

    // check that both accel and gyro are indeed ready
    const std::optional<uint8_t> status_reg = ReadOneReg(spi_device_, Reg::STATUS_REG);
    if (!status_reg) {
      ESP_LOGE(TAG, "cannot get status reg");
      portYIELD();
      continue;
    }
    if ((*status_reg & 0x03) != 0x03) {
      portYIELD();
      continue;
    }
    if (ReadRegs(spi_device_, Reg::OUT_TEMP_L, sizeof(buf), buf) != ESP_OK) {
      ESP_LOGE(TAG, "cannot start SPI transaction");
      continue;
    }
    data = {
        .capture = capture,
        .temperature = Uint16LeAt(buf + 0),
        .wx = Sint16LeAt(buf + 2),
        .wy = Sint16LeAt(buf + 4),
        .wz = Sint16LeAt(buf + 6),
        .ax = Sint16LeAt(buf + 8),
        .ay = Sint16LeAt(buf + 10),
        .az = Sint16LeAt(buf + 12),
    };
    if (subscriber_) {
      subscriber_(data);
    }
  }
}
