// Copyright (c) rice-timer authors
#pragma once

#include <cstdint>

enum class Lsm6DataRate : uint8_t {
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

enum class Lsm6AccelFullScale : uint8_t {
  kAccelFs2g = 0b00,
  kAccelFs16g = 0b01,
  kAccelFs4g = 0b10,
  kAccelFs8g = 0b11,
};

enum class Lsm6GyroFullScale : uint8_t {
  kGyroFs250Dps = 0b0000,
  kGyroFs4000Dps = 0b0001,
  kGyroFs125Dps = 0b0010,
  kGyroFs500Dps = 0b0100,
  kGyroFs1000Dps = 0b1000,
  kGyroFs2000Dps = 0b1100,
};


bool Lsm6IsConnected();
void Lsm6Configure(
    Lsm6DataRate data_rate,
    Lsm6AccelFullScale accel_full_scale,
    Lsm6GyroFullScale gyro_full_scale);
