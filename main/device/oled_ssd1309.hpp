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
  esp_err_t SetFlipLr(bool flipped);
  esp_err_t SetFlipUd(bool flipped);

  void SetPixel(uint8_t row, uint8_t col, bool on);
  esp_err_t Flush();

  std::array<uint8_t, kNativePixels / 8>& mutable_buf() { return buf_; }

  esp_err_t RegisterLvglDriver();

  DEFINE_CREATE(OledSsd1309)

 private:
  enum Flag {
    kFlagDisplayEnabled = 0,
    kFlagDisplayAllOn,
    kFlagDisplayInverted,
    kFlagFlipLr,
    kFlagFlipUd,
    kNumFlags,
  };
  static constexpr uint8_t kNop = 0xE3;
  static constexpr uint8_t kFlagCommands[kNumFlags][2]{
      {0xAE, 0xAF},  // off / on
      {0xA4, 0xA5},  // normal / all on
      {0xA6, 0xA7},  // normal / inverted
      {0xA0, 0xA1},  // normal / flip LR
      {0xC0, 0xC8},  // normal / flip UD
  };
  static constexpr uint8_t kFixedConfigCommands[][2]{
      {0xFD, 0x12},  // unlock
      {0xD5, 0xA0},  // clock setup
      {0xA8, 0x3F},  // multiplex ratio: 63 + 1 = 64
      {0xDA, 0x12},  // interleave mode
      {0x81, 0xA0},  // current control
      {0xD9, 0x84},  // pre-charge period
      {0xDB, 0x34},  // VCOMH deselect level
      {0x20, 0x00},  // horizontal address mode
      {0xD3, 0x00},  // display offset = 0
      {0x40, kNop},  // display start line = 0
  };
  static constexpr uint8_t kNumFixedConfigCommands =
      sizeof(kFixedConfigCommands) / sizeof(kFixedConfigCommands[0]);
  static constexpr int kNumCommands = kNumFlags + kNumFixedConfigCommands;

  // mirror image of VRAM (8R x 1C packed into 1 byte)
  std::array<uint8_t, kNativePixels / 8> buf_{};

  lv_disp_draw_buf_t lv_disp_draw_buf_;
  lv_disp_drv_t lv_disp_drv_;

  Option option_;
  spi_device_handle_t spi_device_{};
  spi_transaction_t spi_data_txn_{};

  std::array<bool, kNumFlags> flags_{};
  uint8_t rolling_command_index_ = 0;

  explicit OledSsd1309(Option option);

  esp_err_t Setup();

  std::pair<uint8_t, uint8_t> GetCommand(int index);
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
