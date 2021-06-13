// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <array>
#include <memory>

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "lvgl.h"

#include "common/macros.hpp"

class OledSsd1309 {
 public:
  // SSD1309 is a fixed 128 x 64 chip
  static constexpr int kNativeWidth = 128;
  static constexpr int kNativeHeight = 64;
  static constexpr int kNativePixels = kNativeWidth * kNativeHeight;

  struct Option {
    spi_host_device_t spi = VSPI_HOST;
    gpio_num_t cs_pin = GPIO_NUM_NC;
    gpio_num_t dc_pin = GPIO_NUM_NC;
  };

  esp_err_t SetDisplayEnabled(bool enabled);
  esp_err_t SetDisplayAllOn(bool enabled);
  esp_err_t SetDisplayInverted(bool inverted);

  esp_err_t SetFlipLR(bool flipped);
  esp_err_t SetFlipUD(bool flipped);

  esp_err_t Flush();

  std::array<uint8_t, kNativePixels / 8>& mutable_buf() { return buf_; }

  esp_err_t RegisterLvglDriver();

  DEFINE_CREATE(OledSsd1309)

 private:
  // mirror image of VRAM (8R x 1C packed into 1 byte)
  std::array<uint8_t, kNativePixels / 8> buf_;

  lv_disp_buf_t lv_disp_buf_;
  lv_disp_drv_t lv_disp_drv_;

  Option option_;
  spi_device_handle_t spi_device_;
  spi_transaction_t spi_data_txn_{};

  explicit OledSsd1309(Option option);

  esp_err_t Setup();

  esp_err_t SendCommand(const uint8_t* command, int len);
  esp_err_t SendData(const uint8_t* data, int len);

  static void LvglSetPx(
      lv_disp_drv_t* disp_drv,
      uint8_t* buf,
      lv_coord_t buf_w,
      lv_coord_t x,
      lv_coord_t y,
      lv_color_t color,
      lv_opa_t opa);
};
