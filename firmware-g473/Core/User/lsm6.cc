// Copyright (c) rice-timer authors
#include "lsm6.h"

#include "sensor_input.h"

bool Lsm6IsConnected() {
  const uint8_t who_am_i = SensorInputReadImuReg(static_cast<uint8_t>(Lsm6Reg::WHO_AM_I));
  return who_am_i == 0x6B;
}

void Lsm6Configure(
    Lsm6DataRate data_rate,
    Lsm6AccelFullScale accel_full_scale,
    Lsm6GyroFullScale gyro_full_scale) {
  if (!Lsm6IsConnected()) {
    return;
  }
  SensorInputWriteImuReg(
      static_cast<uint8_t>(Lsm6Reg::CTRL1_XL),
      (static_cast<uint8_t>(data_rate) << 4) | (static_cast<uint8_t>(accel_full_scale) << 2));
  SensorInputWriteImuReg(
      static_cast<uint8_t>(Lsm6Reg::CTRL2_G),
      (static_cast<uint8_t>(data_rate) << 4) | (static_cast<uint8_t>(gyro_full_scale) << 0));
  SensorInputWriteImuReg(
      static_cast<uint8_t>(Lsm6Reg::CTRL4_C),
      0b00000100);  // I2C_disable
  SensorInputWriteImuReg(
      static_cast<uint8_t>(Lsm6Reg::INT2_CTRL),
      0b00000011);  // INT2_DRDY_G, INT2_DRDY_XL
}
