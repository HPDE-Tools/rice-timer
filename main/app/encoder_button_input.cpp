// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/encoder_button_input.hpp"

#include <cmath>

#include "driver/adc.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "common/macros.hpp"
#include "common/utils.hpp"
#include "device/encoder.hpp"
#include "math/polyfill.hpp"

namespace app {

namespace {

static constexpr char TAG[] = "indev";

constexpr double kVdd = 3.3;
constexpr double kVref = 1.1;
constexpr double k11Db = 0.281838293;  // == 10^(-11/20)
constexpr int kAdcMax = (1 << 12) - 1;
constexpr double kButton1Nominal = kVdd * (3.3 / (3.3 + 10.0)) * k11Db / kVref * kAdcMax;
constexpr double kButton2Nominal = kVdd * (10.0 / (10.0 + 10.0)) * k11Db / kVref * kAdcMax;
constexpr double kButton3Nominal = kVdd * (30.0 / (30.0 + 10.0)) * k11Db / kVref * kAdcMax;
constexpr int kButton1Low = std::lerp(kButton1Nominal, 0.0, 1.0 / 3);
constexpr int kButton1High = std::lerp(kButton1Nominal, kButton2Nominal, 1.0 / 3);
constexpr int kButton2Low = std::lerp(kButton2Nominal, kButton1Nominal, 1.0 / 3);
constexpr int kButton2High = std::lerp(kButton2Nominal, kButton3Nominal, 1.0 / 3);
constexpr int kButton3Low = std::lerp(kButton3Nominal, kButton2Nominal, 1.0 / 3);
constexpr int kButton3High = std::lerp(kButton3Nominal, kAdcMax * 1.0, 1.0 / 3);

adc1_channel_t g_adc_channel = ADC1_CHANNEL_0;
gpio_num_t g_adc_pin = GPIO_NUM_36;

std::unique_ptr<Encoder> g_encoder;

esp_err_t SetupAdc() {
  TRY(adc1_config_width(ADC_WIDTH_BIT_12));
  TRY(adc1_config_channel_atten(g_adc_channel, ADC_ATTEN_11db));
  return ESP_OK;
}

uint16_t PollAdc() {
  constexpr int kMinPollPeriodMs = 50;

  static uint16_t result = 0;
  static TickType_t last_poll_time = xTaskGetTickCount() - pdMS_TO_TICKS(kMinPollPeriodMs);
  const TickType_t now = xTaskGetTickCount();
  if (SignedMinus(now, last_poll_time) < pdMS_TO_TICKS(kMinPollPeriodMs)) {
    return result;
  }
  last_poll_time = now;
  result = adc1_get_raw(g_adc_channel);
  return result;
}

esp_err_t RegisterEncoderDriver() {
  constexpr uint16_t kFilterValue = APB_CLK_FREQ * 10e-6;

  g_encoder = Encoder::Create(Encoder::Option{
      .unit = PCNT_UNIT_0,
      .a_pin = GPIO_NUM_22,
      .b_pin = GPIO_NUM_21,
      .filter_value = kFilterValue,
  });
  if (!g_encoder) {
    return ESP_ERR_NO_MEM;
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
    const uint16_t button_raw = PollAdc();
    if (kButton2Low <= button_raw && button_raw < kButton2High) {
      ESP_LOGD(TAG, "btn2");
      data->state = LV_INDEV_STATE_PR;
    } else {
      data->state = LV_INDEV_STATE_REL;
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
  driver.read_cb = [](lv_indev_drv_t* drv, lv_indev_data_t* data) {
    const uint16_t button_raw = PollAdc();
    // TODO(summivox): state machine (only allow 1KRO)
    if (kButton1Low <= button_raw && button_raw < kButton1High) {
      ESP_LOGD(TAG, "btn1");
      data->key = LV_KEY_PREV;
      data->state = LV_INDEV_STATE_PR;
    } else if (kButton3Low <= button_raw && button_raw < kButton3High) {
      ESP_LOGD(TAG, "btn3");
      data->key = LV_KEY_NEXT;
      data->state = LV_INDEV_STATE_PR;
    } else {
      data->state = LV_INDEV_STATE_REL;
    }
    return false;
  };
  g_buttons_indev = lv_indev_drv_register(&driver);
  return g_buttons_indev ? ESP_OK : ESP_FAIL;
}

}  // namespace

lv_indev_t* g_encoder_indev{};
lv_indev_t* g_buttons_indev{};

esp_err_t RegisterLvglInputDrivers() {
  if constexpr (CONFIG_HW_VERSION != 3) {
    return ESP_ERR_NOT_SUPPORTED;
  }

  // ADC1_CH0 = SENSOR_VP = GPIO36
  g_adc_channel = ADC1_CHANNEL_0;
  g_adc_pin = GPIO_NUM_36;
  TRY(SetupAdc());

  TRY(RegisterEncoderDriver());
  TRY(RegisterButtonDriver());
  return ESP_OK;
}

}  // namespace app
