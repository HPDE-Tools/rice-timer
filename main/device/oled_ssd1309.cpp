// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/oled_ssd1309.hpp"

#include <array>

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"

#include "common/logging.hpp"
#include "common/utils.hpp"

namespace {

constexpr char TAG[] = "ssd1309";

void* DcPinCommand(gpio_num_t pin) { return reinterpret_cast<void*>(~static_cast<int32_t>(pin)); }
void* DcPinData(gpio_num_t pin) { return reinterpret_cast<void*>(static_cast<int32_t>(pin)); }

esp_err_t SetupSpi(
    spi_host_device_t spi,
    gpio_num_t cs_pin,
    gpio_num_t dc_pin,
    spi_device_handle_t* out_spi_device) {
  gpio_pad_select_gpio(dc_pin);
  TRY(gpio_set_direction(dc_pin, GPIO_MODE_OUTPUT));
  spi_device_interface_config_t spi_device_config = {
      .command_bits = 0,
      .address_bits = 0,
      .dummy_bits = 0,
      .mode = 3,
      .duty_cycle_pos = 128,
      .cs_ena_pretrans = 1,
      .cs_ena_posttrans = 1,
      .clock_speed_hz = SPI_MASTER_FREQ_10M,
      .input_delay_ns = 0,
      .spics_io_num = cs_pin,
      .flags = SPI_DEVICE_HALFDUPLEX | SPI_DEVICE_3WIRE,
      .queue_size = 4,
      .pre_cb =
          [](spi_transaction_t* trans) {
            auto pin_and_level = reinterpret_cast<int32_t>(trans->user);
            if (pin_and_level >= 0) {
              gpio_set_level(static_cast<gpio_num_t>(pin_and_level), 1);
            } else {
              gpio_set_level(static_cast<gpio_num_t>(~pin_and_level), 0);
            }
          },
      .post_cb =
          [](spi_transaction_t* trans) {
            auto pin_and_level = reinterpret_cast<int32_t>(trans->user);
            if (pin_and_level >= 0) {
              gpio_set_level(static_cast<gpio_num_t>(pin_and_level), 0);
            } else {
              gpio_set_level(static_cast<gpio_num_t>(~pin_and_level), 0);
            }
          },
  };
  return spi_bus_add_device(spi, &spi_device_config, out_spi_device);
}

}  // namespace

std::pair<uint8_t, uint8_t> OledSsd1309::GetCommand(int index) {
  CHECK(0 <= index && index < kNumCommands);
  if (index < kNumFlags) {
    return {kFlagCommands[index][flags_[index]], kNop};
  }
  index -= kNumFlags;
  return {kFixedConfigCommands[index][0], kFixedConfigCommands[index][1]};
}

esp_err_t OledSsd1309::SendCommand(const uint8_t* command, int len) {
  spi_transaction_t txn{};
  txn.length = len * 8;
  txn.tx_buffer = command;
  txn.user = DcPinCommand(option_.dc_pin);
  return spi_device_polling_transmit(spi_device_, &txn);
}

esp_err_t OledSsd1309::SendData(const uint8_t* data, int len) {
  spi_data_txn_.length = len * 8;
  spi_data_txn_.tx_buffer = data;
  spi_data_txn_.user = DcPinData(option_.dc_pin);
  return spi_device_transmit(spi_device_, &spi_data_txn_);
}

OledSsd1309::OledSsd1309(Option option) : option_(option) {
  // NOTE: address of the buffer is the same address as the driver object.
  // This makes it easy to recover the driver object from C API.
  static_assert(offsetof(OledSsd1309, buf_) == 0);
  std::fill(buf_.begin(), buf_.end(), 0u);
}

esp_err_t OledSsd1309::Setup() {
  // first things to do when powering up: unlock commands and turn off the screen
  constexpr uint8_t preamble[]{0xFD, 0x12, 0xAE};

  TRY(SetupSpi(option_.spi, option_.cs_pin, option_.dc_pin, &spi_device_));
  TRY(SendCommand(preamble, sizeof(preamble)));
  for (int i = 0; i < kNumCommands; i++) {
    uint8_t command[2];
    std::tie(command[0], command[1]) = GetCommand(i);
    TRY(SendCommand(command, 2));
  }
  return ESP_OK;
}

esp_err_t OledSsd1309::SetDisplayEnabled(bool enabled) {
  flags_[kFlagDisplayEnabled] = enabled;
  const auto [command, _] = GetCommand(kFlagDisplayEnabled);
  return SendCommand(&command, 1);
}
esp_err_t OledSsd1309::SetDisplayAllOn(bool enabled) {
  flags_[kFlagDisplayAllOn] = enabled;
  const auto [command, _] = GetCommand(kFlagDisplayAllOn);
  return SendCommand(&command, 1);
}
esp_err_t OledSsd1309::SetDisplayInverted(bool inverted) {
  flags_[kFlagDisplayInverted] = inverted;
  const auto [command, _] = GetCommand(kFlagDisplayInverted);
  return SendCommand(&command, 1);
}
esp_err_t OledSsd1309::SetFlipLr(bool flipped) {
  flags_[kFlagFlipLr] = flipped;
  const auto [command, _] = GetCommand(kFlagFlipLr);
  return SendCommand(&command, 1);
}
esp_err_t OledSsd1309::SetFlipUd(bool flipped) {
  flags_[kFlagFlipUd] = flipped;
  const auto [command, _] = GetCommand(kFlagFlipUd);
  return SendCommand(&command, 1);
}

void OledSsd1309::SetPixel(uint8_t row, uint8_t col, bool on) {
  const uint8_t page = row / 8;
  const uint8_t bit = row % 8;
  if (on) {
    buf_[page * kNativeWidth + col] |= 1 << bit;
  } else {
    buf_[page * kNativeWidth + col] &= ~(1 << bit);
  }
}

esp_err_t OledSsd1309::Flush() {
  // clang-format off
  uint8_t command[] = {
    kNop, kNop,  // slot for 2-byte rolling command
    0x21, 0, 127,  // column (segment) range
    0x22, 0, 7,  // page (8-row) range
  };
  // clang-format on
  std::tie(command[0], command[1]) = GetCommand(rolling_command_index_);
  if (++rolling_command_index_ >= kNumCommands) {
    rolling_command_index_ = 0;
  }
  TRY(SendCommand(command, sizeof(command)));
  TRY(SendData(buf_.data(), buf_.size()));
  return ESP_OK;
}

esp_err_t OledSsd1309::RegisterLvglDriver() {
  lv_disp_buf_init(&lv_disp_buf_, buf_.data(), /*buf2*/ nullptr, kNativePixels);
  lv_disp_drv_init(&lv_disp_drv_);
  lv_disp_drv_.hor_res = kNativeWidth;
  lv_disp_drv_.ver_res = kNativeHeight;
  lv_disp_drv_.dpi = 59;
  lv_disp_drv_.rounder_cb = [](lv_disp_drv_t* disp_drv, lv_area_t* area) {
    area->x1 = 0;
    area->x2 = kNativeWidth - 1;
    area->y1 = 0;
    area->y2 = kNativeHeight - 1;
  };
  lv_disp_drv_.flush_cb = [](lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_map) {
    auto self = reinterpret_cast<OledSsd1309*>(drv->buffer->buf1);
    (void)self->Flush();  // NOTE: no way to report failure here
    lv_disp_flush_ready(drv);
  };
  lv_disp_drv_.set_px_cb = LvglSetPx;
  lv_disp_drv_.buffer = &lv_disp_buf_;
  if (lv_disp_drv_register(&lv_disp_drv_) == nullptr) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

// NOTE: LVGL defaults to black-on-white for mono displays, so we use the following
// pixel mapping to avoid having to double-invert everything.
//
//  | lv_color_t     | bit in buffer | OLED  |
//  |----------------|---------------|-------|
//  | LV_COLOR_WHITE | 0             | off   |
//  | LV_COLOR_BLACK | 1             | on    |
//
void OledSsd1309::LvglSetPx(
    lv_disp_drv_t* disp_drv,
    uint8_t* buf,
    lv_coord_t buf_w,
    lv_coord_t x,
    lv_coord_t y,
    lv_color_t color,
    lv_opa_t opa) {
  auto self = reinterpret_cast<OledSsd1309*>(buf);
  self->SetPixel(y, x, !color.full);
}
