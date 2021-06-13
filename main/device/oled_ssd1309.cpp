// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/oled_ssd1309.hpp"

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"

#include "common/logging.hpp"

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
}

esp_err_t OledSsd1309::Setup() {
  // clang-format off
  constexpr uint8_t init_command[] {
    0xFD, 0x12,  // unlock
    0xAE,        // display off
    0xA4,        // no display all on
    0xA6,        // polarity: 0=black, 1=white

    // ==== panel-specific settings ====
    0xD5, 0xA0,  // clock
    0xA8, 0x3F,  // multiplex ratio: 63 + 1 = 64
    0xDA, 0x12,  // interleave mode
    0x81, 0x7F,  // current control
    0xD9, 0x82,  // pre-charge period
    0xDB, 0x34,  // VCOMH deselect level

    // ==== reset geometry settings ====
    0xD3, 0x00,  // display offset
    0x40,        // display start line
    0xA0,        // LR no flip
    0xC0,        // UD no flip

    // ==== VRAM addressing settings ====
    0x20, 0x20,    // horizontal addressing mode
    0x21, 0, 127,  // column range
    0x22, 0, 7,    // page (8-row) range
  };
  // clang-format on

  TRY(SetupSpi(option_.spi, option_.cs_pin, option_.dc_pin, &spi_device_));
  TRY(SendCommand(init_command, sizeof(init_command)));
  return ESP_OK;
}

esp_err_t OledSsd1309::SetDisplayEnabled(bool enabled) {
  uint8_t command = enabled ? 0xAF : 0xAE;
  return SendCommand(&command, 1);
}
esp_err_t OledSsd1309::SetDisplayAllOn(bool enabled) {
  uint8_t command = enabled ? 0xA5 : 0xA4;
  return SendCommand(&command, 1);
}
esp_err_t OledSsd1309::SetDisplayInverted(bool inverted) {
  uint8_t command = inverted ? 0xA7 : 0xA6;
  return SendCommand(&command, 1);
}

esp_err_t OledSsd1309::Flush() {
  TRY(SendData(buf_.data(), buf_.size()));
  return ESP_OK;
}

esp_err_t OledSsd1309::RegisterLvglDriver() {
  lv_disp_buf_init(&lv_disp_buf_, buf_.data(), /*buf2*/ nullptr, buf_.size());
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
    ESP_LOGE(TAG, "flush");
    self->Flush();
    lv_disp_flush_ready(drv);
  };
  lv_disp_drv_.set_px_cb = LvglSetPx;
  lv_disp_drv_.buffer = &lv_disp_buf_;
  if (lv_disp_drv_register(&lv_disp_drv_) == nullptr) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

void OledSsd1309::LvglSetPx(
    lv_disp_drv_t* disp_drv,
    uint8_t* buf,
    lv_coord_t buf_w,
    lv_coord_t x,
    lv_coord_t y,
    lv_color_t color,
    lv_opa_t opa) {
  ESP_LOGE(TAG, "set(%d,%d)", x, y);
  const int page = y / 8;
  const int bit = y % 8;
  if (color.full) {
    buf[page * kNativeWidth + x] |= (1u << bit);
  } else {
    buf[page * kNativeWidth + x] &= ~(1u << bit);
  }
}
