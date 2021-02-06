// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "esp_err.h"

#include "capture_manager.hpp"
#include "common/task.hpp"

class Lsm6dsr : Task {
 public:
#include "device/imu_driver_lsm6dsr_reg.inl"
  enum OutputDataRate : uint8_t {
    kDisabled = 0b0000,
    kOdr12p5Hz = 0b0001,
    kOdr26Hz = 0b0010,
    kOdr52Hz = 0b0011,
    kOdr104Hz = 0b0100,
    kOdr208Hz = 0b0101,
    kOdr417Hz = 0b0110,
    kOdr833Hz = 0b0111,
    kOdr1667Hz = 0b1000,
    kOdr3333Hz = 0b1001,
    kOdr6667Hz = 0b1010,
  };
  enum AccelFullScale : uint8_t {
    kAccelFs2g = 0b00,
    kAccelFs16g = 0b01,
    kAccelFs4g = 0b10,
    kAccelFs8g = 0b11,
  };
  enum GyroFullScale : uint8_t {
    kGyroFs250Dps = 0b0000,
    kGyroFs4000Dps = 0b0001,
    kGyroFs125Dps = 0b0010,
    kGyroFs500Dps = 0b0100,
    kGyroFs1000Dps = 0b1000,
    kGyroFs2000Dps = 0b1100,
  };
  struct Option {
    spi_host_device_t spi = VSPI_HOST;
    gpio_num_t cs_pin = GPIO_NUM_NC;
    gpio_num_t interrupt_pin = GPIO_NUM_NC;

    OutputDataRate accel_output_data_rate = kDisabled;
    AccelFullScale accel_full_scale = kAccelFs2g;
    OutputDataRate gyro_output_data_rate = kDisabled;
    GyroFullScale gyro_full_scale = kGyroFs250Dps;

    int priority = 0;
  };

  struct RawImuData {
    uint32_t capture;
    uint16_t temperature;
    int16_t wx;
    int16_t wy;
    int16_t wz;
    int16_t ax;
    int16_t ay;
    int16_t az;
  };

  using RawImuDataSubscriber = std::function<void(const RawImuData& data)>;

  static std::unique_ptr<Lsm6dsr> Create(CaptureChannel interrupt_capture, Option option) {
    std::unique_ptr<Lsm6dsr> self{new Lsm6dsr(interrupt_capture, option)};
    if (self->Setup() != ESP_OK) {
      self.reset();
    }
    return self;
  }
  virtual ~Lsm6dsr();

  esp_err_t Start(RawImuDataSubscriber subscriber);
  void Stop();

 protected:
  void Run() override;

 private:
  Option option_;
  const CaptureChannel capture_;
  spi_device_handle_t spi_device_;
  RawImuDataSubscriber subscriber_;

  Lsm6dsr(CaptureChannel interrupt_capture, Option option);
  esp_err_t Setup();
  void Teardown();
};
