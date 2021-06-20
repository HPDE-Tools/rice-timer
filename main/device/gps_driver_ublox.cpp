// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/gps_driver_ublox.hpp"

#include <utility>
#include <vector>

#include "common/logging.hpp"
#include "common/scope_guard.hpp"
#include "device/gps_utils.hpp"
#include "io/autobaud.hpp"

#define UINT16_LE_BYTES(x) uint8_t(x), uint8_t(((x) >> 8))
#define UINT32_LE_BYTES(x) uint8_t(x), uint8_t((x) >> 8), uint8_t((x) >> 16), uint8_t((x) >> 24)

namespace {

constexpr uint8_t kUbxSync1 = 0xB5;
constexpr uint8_t kUbxSync2 = 0x62;

struct UbxFrame {
  union {
    struct {
      uint8_t class_id;
      uint8_t message_id;
      mutable uint16_t len;
    } header;
    uint8_t header_bytes[4];
  };
  std::vector<uint8_t> payload;

  std::pair<uint8_t, uint8_t> GetChecksum() const {
    uint8_t a{};
    uint8_t b{};
    header.len = payload.size();
    for (const uint8_t x : header_bytes) {
      a += x;
      b += a;
    }
    for (const uint8_t x : payload) {
      a += x;
      b += a;
    }
    return {a, b};
  }
};

esp_err_t UbxI2cSendFrame(i2c_port_t i2c_num, uint8_t i2c_address_7bit, const UbxFrame& frame) {
  i2c_cmd_handle_t txn = i2c_cmd_link_create();

  i2c_master_start(txn);
  i2c_master_write_byte(txn, (i2c_address_7bit << 1) | I2C_MASTER_WRITE, /*ack*/ true);
  i2c_master_write_byte(txn, 0xFF, /*ack*/ true);

  const auto [a, b] = frame.GetChecksum();

  i2c_master_start(txn);
  i2c_master_write_byte(txn, (i2c_address_7bit << 1) | I2C_MASTER_WRITE, /*ack*/ true);
  i2c_master_write_byte(txn, kUbxSync1, /*ack*/ true);
  i2c_master_write_byte(txn, kUbxSync2, /*ack*/ true);
  i2c_master_write(txn, frame.header_bytes, 4, /*ack*/ true);
  i2c_master_write(txn, frame.payload.data(), frame.payload.size(), /*ack*/ true);

  i2c_master_write_byte(txn, a, /*ack*/ true);
  i2c_master_write_byte(txn, b, /*ack*/ true);

  i2c_master_stop(txn);
  return i2c_master_cmd_begin(i2c_num, txn, portMAX_DELAY);
}

std::optional<UbxFrame> UbxI2cReceiveOneFrame(i2c_port_t i2c_num, uint8_t i2c_address_7bit) {
  std::optional<UbxFrame> result{};
  i2c_cmd_handle_t txn = i2c_cmd_link_create();
  i2c_master_start(txn);
  i2c_master_write_byte(txn, (i2c_address_7bit << 1) | I2C_MASTER_WRITE, /*ack*/ true);
  i2c_master_write_byte(txn, 0xFD, /*ack*/ true);
  i2c_master_start(txn);
  i2c_master_write_byte(txn, (i2c_address_7bit << 1) | I2C_MASTER_READ, /*ack*/ true);
  uint8_t len_raw[2];
  // TODO

  return result;
}

};  // namespace

esp_err_t SetupUbloxGpsI2c(
    i2c_port_t i2c_num, uint8_t i2c_address_7bit, int desired_baud, int desired_output_period_ms) {
  const UbxFrame ubx_cfg_port = {
      .header = {.class_id = 0x06, .message_id = 0x00},
      .payload = {
          1,                              // portID = UART1
          0,                              // reserved1
          UINT16_LE_BYTES(0),             // txReady
          UINT32_LE_BYTES(0x08C0),        // mode = 8N1
          UINT32_LE_BYTES(desired_baud),  // baud
          UINT16_LE_BYTES(0b000011),      // inProtoMask = NMEA | UBX
          UINT16_LE_BYTES(0b000010),      // outProtoMask = NMEA
          UINT16_LE_BYTES(0x0002),        // flags
          UINT16_LE_BYTES(0),             // reserved2
      }};
  TRY(UbxI2cSendFrame(i2c_num, i2c_address_7bit, ubx_cfg_port));

  const UbxFrame ubx_cfg_rate = {
      .header = {.class_id = 0x06, .message_id = 0x08},
      .payload = {
          UINT16_LE_BYTES(desired_output_period_ms),  // measRate
          UINT16_LE_BYTES(1),                         // navRate (divider)
          UINT16_LE_BYTES(1),                         // timeRef
      }};
  TRY(UbxI2cSendFrame(i2c_num, i2c_address_7bit, ubx_cfg_rate));

  return ESP_OK;
}
