// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/gps_driver_ublox.hpp"

#include <algorithm>

#include "common/i2c_helpers.hpp"
#include "common/macros.hpp"
#include "device/gps_utils.hpp"

namespace {
constexpr char TAG[] = "ubx";

template <typename Lambda>
esp_err_t DelayRetry(
    int max_num_retry, TickType_t init_delay, TickType_t max_delay, Lambda lambda) {
  esp_err_t result{};
  TickType_t delay = init_delay;
  for (int i = 0; i < max_num_retry; i++) {
    result = lambda();
    if (result == ESP_OK) {
      return result;
    }
    vTaskDelay(delay);
    delay = std::min(delay * 3 / 2, max_delay);
  }
  return result;
}

}  // namespace

UbxFrame::UbxFrame(uint8_t class_id, uint8_t message_id, uint16_t len)
    : header_{class_id, message_id, len} {
  payload_ = std::make_unique<uint8_t[]>(len);
}

UbxFrame::UbxFrame(uint8_t class_id, uint8_t message_id, std::initializer_list<uint8_t> payload) {
  CHECK(payload.size() <= UINT16_MAX);
  header_.class_id = class_id;
  header_.message_id = message_id;
  header_.len = payload.size();
  payload_ = std::make_unique<uint8_t[]>(payload.size());
  std::copy(payload.begin(), payload.end(), payload_.get());
}

std::pair<uint8_t, uint8_t> UbxFrame::GetChecksum() const {
  uint8_t a{};
  uint8_t b{};
  for (const uint8_t x : header_bytes_) {
    a += x;
    b += a;
  }
  for (int i = 0; i < header_.len; i++) {
    a += payload_[i];
    b += a;
  }
  return {a, b};
}

esp_err_t UbxI2cSendFrame(i2c_port_t i2c_num, uint8_t i2c_address_7bit, const UbxFrame& frame) {
  const auto [a, b] = frame.GetChecksum();
  return I2cTxn()
      .StartWrite(i2c_address_7bit)
      .WriteByte(kUbxI2cRegData)
      .StartWrite(i2c_address_7bit)
      .WriteByte(kUbxSync1)
      .WriteByte(kUbxSync2)
      .Write(frame.header_bytes().data(), 4)
      .Write(frame.payload(), frame.len())
      .WriteByte(a)
      .WriteByte(b)
      .Stop()
      .SendTo(i2c_num);
}

std::optional<uint16_t> UbxI2cGetNumBytesAvailable(i2c_port_t i2c_num, uint8_t i2c_address_7bit) {
  uint8_t result[2];
  OK_OR_RETURN(
      I2cTxn()
          .StartWrite(i2c_address_7bit)
          .WriteByte(kUbxI2cRegLen)
          .Start()
          .StartRead(i2c_address_7bit)
          .Read(result, 2)
          .Stop()
          .SendTo(i2c_num),
      {});
  return Uint16LeAt(result);
}

esp_err_t SetupUbloxGpsI2c(
    i2c_port_t i2c_num,
    uint8_t i2c_address_7bit,
    int desired_uart_baud,
    int desired_output_period_ms) {
  const UbxFrame ubx_cfg_port_i2c{
      0x06,  // CFG
      0x00,  // CFG-PORT
      {
          0,                                       // portID = DDC (I2C)
          0,                                       // reserved1
          UINT16_LE_BYTES(0),                      // txReady
          UINT32_LE_BYTES(i2c_address_7bit << 1),  // mode = keep current slave addr
          UINT32_LE_BYTES(0),                      // reserved2
          UINT16_LE_BYTES(0b000011),               // inProtoMask = NMEA | UBX
          UINT16_LE_BYTES(0b000001),               // outProtoMask = UBX
          UINT16_LE_BYTES(0x0002),                 // flags = extendedTxTimeout
          UINT16_LE_BYTES(0),                      // reserved3
      },
  };
  TRY(UbxI2cSendFrame(i2c_num, i2c_address_7bit, ubx_cfg_port_i2c));

  const UbxFrame ubx_cfg_port_uart1{
      0x06,  // CFG
      0x00,  // CFG-PORT
      {
          1,                                   // portID = UART1
          0,                                   // reserved1
          UINT16_LE_BYTES(0),                  // txReady
          UINT32_LE_BYTES(0x08C0),             // mode = 8N1
          UINT32_LE_BYTES(desired_uart_baud),  // baud
          UINT16_LE_BYTES(0b000011),           // inProtoMask = NMEA | UBX
          UINT16_LE_BYTES(0b000010),           // outProtoMask = NMEA
          UINT16_LE_BYTES(0x0002),             // flags = extendedTxTimeout
          UINT16_LE_BYTES(0),                  // reserved2
      },
  };
  TRY(UbxI2cSendFrame(i2c_num, i2c_address_7bit, ubx_cfg_port_uart1));

  for (const auto [mnemonic, cls, id, rate] : kNmeaMessages) {
    ESP_LOGI(TAG, "%c%c%c%c = %d", UINT32_BE_BYTES(mnemonic), rate);
    const UbxFrame ubx_cfg_msg{
        0x06,  // CFG
        0x01,  // CFG_MSG
        {
            cls,
            id,
            0,     // 0 -- I2C
            rate,  // 1 -- UART1
            0,     // 2
            1,     // 3 -- USB
            0,     // 4 -- SPI
            0,     // 5
        },
    };
    TRY(UbxI2cSendFrame(i2c_num, i2c_address_7bit, ubx_cfg_msg));
  }

  // configure output rate
  const UbxFrame ubx_cfg_rate{
      0x06,  // CFG
      0x08,  // CFG_RATE
      {
          UINT16_LE_BYTES(desired_output_period_ms),  // measRate
          UINT16_LE_BYTES(1),                         // navRate (divider)
          UINT16_LE_BYTES(1),                         // timeRef
      },
  };
  TRY(UbxI2cSendFrame(i2c_num, i2c_address_7bit, ubx_cfg_rate));

  // save to battery-backed RAM
  const UbxFrame ubx_cfg_cfg_save{
      0x06,  // CFG
      0x09,  // CFG_CFG
      {
          UINT32_LE_BYTES(0),           // clearMask
          UINT32_LE_BYTES(0x00001F1F),  // saveMask
          UINT32_LE_BYTES(0),           // loadMask
          0b0000'0001,                  // deviceMask = devBBR
      },
  };
  TRY(UbxI2cSendFrame(i2c_num, i2c_address_7bit, ubx_cfg_cfg_save));

  return ESP_OK;
}
