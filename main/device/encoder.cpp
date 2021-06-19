// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/encoder.hpp"

#include "common/logging.hpp"

Encoder::Encoder(Option option) : option_(option) {}

esp_err_t Encoder::Setup() {
  // NOTE: this is adapted from the esp-idf rotary encoder example, but with SW overflow disabled.
  // When counting in 4x mode, overflow arithmetic simply works.
  const pcnt_unit_t unit = option_.unit;

  // Configure channel 0
  pcnt_config_t dev_config = {
      .pulse_gpio_num = option_.a_pin,
      .ctrl_gpio_num = option_.b_pin,
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
  dev_config.pulse_gpio_num = option_.b_pin;
  dev_config.ctrl_gpio_num = option_.a_pin;
  dev_config.pos_mode = PCNT_COUNT_INC;
  dev_config.neg_mode = PCNT_COUNT_DEC;
  dev_config.channel = PCNT_CHANNEL_1;
  TRY(pcnt_unit_config(&dev_config));

  // set filter
  TRY(pcnt_set_filter_value(unit, option_.filter_value));
  TRY(pcnt_filter_enable(unit));

  TRY(pcnt_counter_pause(unit));
  TRY(pcnt_counter_clear(unit));
  TRY(pcnt_counter_resume(unit));

  return ESP_OK;
}

std::optional<int16_t> Encoder::count() const {
  int16_t result{};
  OK_OR_RETURN(pcnt_get_counter_value(option_.unit, &result), {});
  return result;
}
