// Copyright (c) rice-timer authors
#include <spi.hpp>
#include "lsm6.h"
#include "lsm6_reg.h"


bool Lsm6IsConnected() {
  const uint8_t who_am_i = SpiSyncReadImuOne(static_cast<uint8_t>(Lsm6Reg::WHO_AM_I));
  return who_am_i == 0x6B;
}

void Lsm6Configure(
    Lsm6DataRate data_rate,
    Lsm6AccelFullScale accel_full_scale,
    Lsm6GyroFullScale gyro_full_scale) {
  if (!Lsm6IsConnected()) {
    return;
  }
  SpiSyncWriteImuOne(
      static_cast<uint8_t>(Lsm6Reg::CTRL1_XL),
      (static_cast<uint8_t>(data_rate) << 4) | (static_cast<uint8_t>(accel_full_scale) << 2));
  SpiSyncWriteImuOne(
      static_cast<uint8_t>(Lsm6Reg::CTRL2_G),
      (static_cast<uint8_t>(data_rate) << 4) | (static_cast<uint8_t>(gyro_full_scale) << 0));
  SpiSyncWriteImuOne(
      static_cast<uint8_t>(Lsm6Reg::CTRL4_C),
      0b00000100);  // I2C_disable
  SpiSyncWriteImuOne(
      static_cast<uint8_t>(Lsm6Reg::INT2_CTRL),
      0b00000011);  // INT2_DRDY_G, INT2_DRDY_XL
}
