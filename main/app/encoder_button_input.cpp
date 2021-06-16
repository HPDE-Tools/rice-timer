// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/encoder_button_input.hpp"

#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "lvgl.h"

#include "common/logging.hpp"
#include "common/utils.hpp"

namespace app {

namespace {

static constexpr char TAG[] = "encoder";

esp_err_t SetupEncoder(pcnt_unit_t unit, gpio_num_t a_pin, gpio_num_t b_pin, uint16_t filter) {
  // NOTE: this is adapted from the esp-idf rotary encoder example, but with SW overflow disabled.
  // When counting in 4x mode, overflow arithmetic simply works.

  // Configure channel 0
  pcnt_config_t dev_config = {
      .pulse_gpio_num = a_pin,
      .ctrl_gpio_num = b_pin,
      .lctrl_mode = PCNT_MODE_REVERSE,
      .hctrl_mode = PCNT_MODE_KEEP,
      .pos_mode = PCNT_COUNT_DEC,
      .neg_mode = PCNT_COUNT_INC,
      .counter_h_lim = 0,
      .counter_l_lim = 0,
      .unit = unit,
      .channel = PCNT_CHANNEL_0,
  };
  TRY(pcnt_unit_config(&dev_config));

  // Configure channel 1
  dev_config.pulse_gpio_num = b_pin;
  dev_config.ctrl_gpio_num = a_pin;
  dev_config.pos_mode = PCNT_COUNT_INC;
  dev_config.neg_mode = PCNT_COUNT_DEC;
  dev_config.channel = PCNT_CHANNEL_1;
  TRY(pcnt_unit_config(&dev_config));

  // set filter
  TRY(pcnt_set_filter_value(unit, filter));
  TRY(pcnt_filter_enable(unit));

  TRY(pcnt_counter_pause(unit));
  TRY(pcnt_counter_clear(unit));
  TRY(pcnt_counter_resume(unit));

  return ESP_OK;
}

}  // namespace

lv_indev_drv_t g_indev_drv_encoder;

esp_err_t RegisterLvglInputDriver() {
  constexpr uint16_t kFilterValue = APB_CLK_FREQ * 10e-6;

  TRY(SetupEncoder(PCNT_UNIT_0, GPIO_NUM_22, GPIO_NUM_21, kFilterValue));

  lv_indev_drv_init(&g_indev_drv_encoder);
  g_indev_drv_encoder.type = LV_INDEV_TYPE_ENCODER;
  g_indev_drv_encoder.read_cb = [](lv_indev_drv_t* drv, lv_indev_data_t* data) {
    static int16_t last_whole_count_raw{};
    int16_t curr_count_raw = last_whole_count_raw;
    OK_OR_RETURN(pcnt_get_counter_value(PCNT_UNIT_0, &curr_count_raw), false);
    const int16_t diff = SignedMinus(curr_count_raw, last_whole_count_raw);
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
  (void)lv_indev_drv_register(&g_indev_drv_encoder);
  return ESP_OK;
}

}  // namespace app
