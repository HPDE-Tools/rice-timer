// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <array>
#include <memory>
#include <optional>
#include <utility>

#include "driver/i2c.h"
#include "esp_err.h"

constexpr uint8_t kUbxSync1 = 0xB5;
constexpr uint8_t kUbxSync2 = 0x62;
constexpr uint8_t kUbxI2cRegLen = 0xFD;
constexpr uint8_t kUbxI2cRegData = 0xFF;

// mnemonic, cls, id, rate
constexpr std::tuple<uint32_t, uint8_t, uint8_t, uint8_t> kNmeaMessages[] = {
    {uint32_t('DTM '), 0xF0, 0x0A, 0},
    {uint32_t('GBQ '), 0xF0, 0x44, 0},
    {uint32_t('GBS '), 0xF0, 0x09, 0},
    {uint32_t('GGA '), 0xF0, 0x00, 1},
    {uint32_t('GLL '), 0xF0, 0x01, 0},
    {uint32_t('GLQ '), 0xF0, 0x43, 0},
    {uint32_t('GNQ '), 0xF0, 0x42, 0},
    {uint32_t('GNS '), 0xF0, 0x0D, 0},
    {uint32_t('GPQ '), 0xF0, 0x40, 0},
    {uint32_t('GRS '), 0xF0, 0x06, 0},
    {uint32_t('GSA '), 0xF0, 0x02, 0},
    {uint32_t('GST '), 0xF0, 0x07, 1},
    {uint32_t('GSV '), 0xF0, 0x03, 0},
    {uint32_t('RMC '), 0xF0, 0x04, 1},
    {uint32_t('TXT '), 0xF0, 0x41, 0},
    {uint32_t('VLW '), 0xF0, 0x0F, 0},
    {uint32_t('VTG '), 0xF0, 0x05, 0},
    {uint32_t('ZDA '), 0xF0, 0x08, 0},
};

struct UbxHeader {
  uint8_t class_id;
  uint8_t message_id;
  uint16_t len;
};
static_assert(sizeof(UbxHeader) == 4);

class UbxFrame {
 public:
  /// constructs empty frame of known length
  UbxFrame(uint8_t class_id, uint8_t message_id, uint16_t len);

  /// constructs frame from brace list
  UbxFrame(uint8_t class_id, uint8_t message_id, std::initializer_list<uint8_t> payload);

  UbxHeader header() const { return header_; }
  const std::array<uint8_t, 4>& header_bytes() const { return header_bytes_; }
  uint8_t class_id() const { return header_.class_id; }
  uint8_t message_id() const { return header_.message_id; }
  uint16_t len() const { return header_.len; }
  uint8_t* payload() const { return payload_.get(); }

  std::pair<uint8_t, uint8_t> GetChecksum() const;

 private:
  // NOTE: ESP32 is little endian --- consistent with UBX protocol
  union {
    UbxHeader header_;
    std::array<uint8_t, 4> header_bytes_;
  };
  std::unique_ptr<uint8_t[]> payload_;
};

esp_err_t UbxI2cSendFrame(i2c_port_t i2c_num, uint8_t i2c_address_7bit, const UbxFrame& frame);
std::optional<uint16_t> UbxI2cGetNumBytesAvailable(i2c_port_t i2c_num, uint8_t i2c_address_7bit);

esp_err_t SetupUbloxGpsI2c(
    i2c_port_t i2c_num,
    uint8_t i2c_address_7bit,
    int desired_uart_baud,
    int desired_output_period_ms);
