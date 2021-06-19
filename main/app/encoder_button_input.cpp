// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/encoder_button_input.hpp"

#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "lvgl.h"

#include "common/logging.hpp"
#include "common/utils.hpp"
#include "device/encoder.hpp"

namespace app {

namespace {

static constexpr char TAG[] = "input_drivers";

std::unique_ptr<Encoder> g_encoder;

esp_err_t RegisterEncoderDriver() {
  constexpr uint16_t kFilterValue = APB_CLK_FREQ * 10e-6;

  g_encoder = Encoder::Create(Encoder::Option{
      .unit = PCNT_UNIT_0,
      .a_pin = GPIO_NUM_22,
      .b_pin = GPIO_NUM_21,
  });
  if (!g_encoder) {
    return ESP_FAIL;
  }

  lv_indev_drv_t driver;
  lv_indev_drv_init(&driver);
  driver.type = LV_INDEV_TYPE_ENCODER;
  driver.read_cb = [](lv_indev_drv_t* drv, lv_indev_data_t* data) {
    // NOTE: should always return false
    static int16_t last_whole_count_raw{};
    if (!g_encoder) {
      return false;
    }
    const std::optional<int16_t> curr_count_raw = g_encoder->count();
    if (!curr_count_raw) {
      return false;
    }
    const int16_t diff = SignedMinus(*curr_count_raw, last_whole_count_raw);
    const int16_t pos = (diff + 1) / 4;
    const int16_t neg = (diff - 1) / 4;
    if (pos >= 1) {
      data->enc_diff = pos;
      last_whole_count_raw += pos * 4;
      ESP_LOGI(TAG, "enc++ => %d", last_whole_count_raw);
    } else if (neg <= -1) {
      data->enc_diff = neg;
      last_whole_count_raw += neg * 4;
      ESP_LOGI(TAG, "enc-- => %d", last_whole_count_raw);
    }
    return false;
  };
  g_encoder_indev = lv_indev_drv_register(&driver);
  return g_encoder_indev ? ESP_OK : ESP_FAIL;
}

esp_err_t RegisterButtonDriver() {
  lv_indev_drv_t driver;
  lv_indev_drv_init(&driver);
  driver.type = LV_INDEV_TYPE_KEYPAD;
  // TODO: maybe consider keypad?
  return g_buttons_indev ? ESP_OK : ESP_FAIL;
}

}  // namespace

lv_indev_t* g_encoder_indev{};
lv_indev_t* g_buttons_indev{};

esp_err_t RegisterLvglInputDrivers() {
  if constexpr (CONFIG_HW_VERSION != 3) {
    return ESP_ERR_NOT_SUPPORTED;
  }

  TRY(RegisterEncoderDriver());
  return ESP_OK;
}

}  // namespace app
