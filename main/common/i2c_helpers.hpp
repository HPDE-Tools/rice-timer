// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "driver/i2c.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

/// Thin C++ wrapper for the C API of ESP-IDF I2C master transactions.
///
/// Features:
///
/// - builder pattern (calls are chainable)
/// - RTTI (automatic clean up)
///
class I2cTxn {
  /// @example
  /// ```c++
  /// uint8_t data[len];
  /// const esp_err_t err = I2cTxn()
  ///     .StartWrite(i2c_address_7bit)
  ///     .WriteByte(0xFF)
  ///     .StartRead(i2c_address_7bit)
  ///     .Read(data, len)
  ///     .Stop()
  ///     .SendTo(i2c_num);
  /// ```
  ///

 public:
  I2cTxn() : txn_(i2c_cmd_link_create()) {}
  ~I2cTxn() { i2c_cmd_link_delete(txn_); }

  // implicit conversion for easier interop with C API
  operator i2c_cmd_handle_t() { return txn_; }

  esp_err_t SendTo(i2c_port_t i2c_num, TickType_t ticks_to_wait = portMAX_DELAY) {
    return i2c_master_cmd_begin(i2c_num, txn_, ticks_to_wait);
  }

  I2cTxn& Start() {
    i2c_master_start(txn_);
    return *this;
  }
  I2cTxn& StartWrite(uint8_t i2c_address_7bit, bool ack_en = true) {
    i2c_master_start(txn_);
    i2c_master_write_byte(txn_, (i2c_address_7bit << 1) | I2C_MASTER_WRITE, ack_en);
    return *this;
  }
  I2cTxn& StartRead(uint8_t i2c_address_7bit, bool ack_en = true) {
    i2c_master_start(txn_);
    i2c_master_write_byte(txn_, (i2c_address_7bit << 1) | I2C_MASTER_READ, ack_en);
    return *this;
  }
  I2cTxn& Stop() {
    i2c_master_stop(txn_);
    return *this;
  }
  I2cTxn& WriteByte(uint8_t data, bool ack_en = true) {
    i2c_master_write_byte(txn_, data, ack_en);
    return *this;
  }
  I2cTxn& ReadByte(uint8_t* data, i2c_ack_type_t ack = I2C_MASTER_ACK) {
    i2c_master_read_byte(txn_, data, ack);
    return *this;
  }
  I2cTxn& Write(const void* data, size_t data_len, bool ack_en = true) {
    i2c_master_write(txn_, reinterpret_cast<const uint8_t*>(data), data_len, ack_en);
    return *this;
  }
  I2cTxn& Read(void* data, size_t data_len, i2c_ack_type_t ack = I2C_MASTER_LAST_NACK) {
    i2c_master_read(txn_, reinterpret_cast<uint8_t*>(data), data_len, ack);
    return *this;
  }

 private:
  i2c_cmd_handle_t txn_;
};
