// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "esp_err.h"

#include "common/task.hpp"
#include "common/utils.hpp"
#include "device/capture_manager.hpp"

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
    bool spi_three_wire = false;

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

  /// Convert raw accel reading (scalar) to g
  float AccelRawToG(int16_t a) const {
    switch (option_.accel_full_scale) {
      case kAccelFs2g:
        return a * float{2.0f / 32767};
      case kAccelFs4g:
        return a * float{4.0f / 32767};
      case kAccelFs8g:
        return a * float{6.0f / 32767};
      case kAccelFs16g:
        return a * float{8.0f / 32767};
      default:
        return 0.0f;
    }
  }

  /// Convert raw accel reading (scalar) to m/s^2
  float AccelRawToMps2(int16_t a) const { return AccelRawToG(a) * kGravity<float>; }

  /// Convert raw gyro reading (scalar) to deg/s
  float GyroRawToDps(int16_t w) const {
    switch (option_.gyro_full_scale) {
      case kGyroFs125Dps:
        return w * float{125.0f / 32767};
      case kGyroFs250Dps:
        return w * float{250.0f / 32767};
      case kGyroFs500Dps:
        return w * float{500.0f / 32767};
      case kGyroFs1000Dps:
        return w * float{1000.0f / 32767};
      case kGyroFs2000Dps:
        return w * float{2000.0f / 32767};
      case kGyroFs4000Dps:
        return w * float{4000.0f / 32767};
      default:
        return 0;
    }
  }

  /// Convert raw gyro reading (scalar) to rad/s
  float GyroRawToRps(int16_t w) const { return DegToRad(GyroRawToDps(w)); }

 protected:
  IRAM_ATTR void Run() override;

 private:
  Option option_;
  const CaptureChannel capture_;
  spi_device_handle_t spi_device_;
  RawImuDataSubscriber subscriber_;

  Lsm6dsr(CaptureChannel interrupt_capture, Option option);
  esp_err_t Setup();
  void Teardown();
};
