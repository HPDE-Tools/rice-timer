// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/encoder_button_input.hpp"

#include <cmath>

#include "driver/adc.h"
#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "common/macros.hpp"
#include "common/utils.hpp"
#include "device/encoder.hpp"
#include "math/polyfill.hpp"

namespace ui {

namespace {

static constexpr char TAG[] = "indev";

// all voltages in mV

constexpr double kVdd = 3300;
constexpr double kVref = 1100;
constexpr double k11Db = 0.281838293;  // == 10^(-11/20)
constexpr int kAdcMax = (1 << 12) - 1;
constexpr double kButton1Nominal = kVdd * (3.3 / (3.3 + 10.0));
constexpr double kButton2Nominal = kVdd * (10.0 / (10.0 + 10.0));
constexpr double kButton3Nominal = kVdd * (30.0 / (30.0 + 10.0));
constexpr int kButton1Low = std::lerp(kButton1Nominal, 0.0, 1.0 / 3);
constexpr int kButton1High = std::lerp(kButton1Nominal, kButton2Nominal, 1.0 / 3);
constexpr int kButton2Low = std::lerp(kButton2Nominal, kButton1Nominal, 1.0 / 3);
constexpr int kButton2High = std::lerp(kButton2Nominal, kButton3Nominal, 1.0 / 3);
constexpr int kButton3Low = std::lerp(kButton3Nominal, kButton2Nominal, 1.0 / 3);
constexpr int kButton3High = std::lerp(kButton3Nominal, kVdd, 1.0 / 3);

constexpr adc_atten_t kAdcAtten = ADC_ATTEN_11db;
constexpr adc_bits_width_t kAdcWidth = adc_bits_width_t(ADC_WIDTH_BIT_DEFAULT);

// NOTE: two consts due to API discrepancy
constexpr adc_channel_t kAdcChannel = ADC_CHANNEL_0;
constexpr adc1_channel_t kAdc1Channel = ADC1_CHANNEL_0;
constexpr gpio_num_t kAdcPin = GPIO_NUM_36;

esp_adc_cal_characteristics_t g_adc_cal{};

std::unique_ptr<Encoder> g_encoder;

esp_err_t SetupAdc() {
  TRY(adc_gpio_init(ADC_UNIT_1, kAdcChannel));
  TRY(adc1_config_width(kAdcWidth));
  TRY(adc1_config_channel_atten(kAdc1Channel, kAdcAtten));
  TRY(esp_adc_cal_characterize(ADC_UNIT_1, kAdcAtten, kAdcWidth, kVref, &g_adc_cal));
  return ESP_OK;
}

uint32_t PollAdc() {
  constexpr int kMinPollPeriodMs = 25;

  static uint32_t result = 0;
  static TickType_t last_poll_time = xTaskGetTickCount() - pdMS_TO_TICKS(kMinPollPeriodMs);
  const TickType_t now = xTaskGetTickCount();
  if (SignedMinus(now, last_poll_time) < pdMS_TO_TICKS(kMinPollPeriodMs)) {
    return result;
  }
  last_poll_time = now;
  esp_adc_cal_get_voltage(kAdcChannel, &g_adc_cal, &result);
  ESP_LOGD("adc", "%d", (int)result);
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

  static lv_indev_drv_t driver;
  lv_indev_drv_init(&driver);
  driver.type = LV_INDEV_TYPE_ENCODER;
  driver.read_cb = [](lv_indev_drv_t* drv, lv_indev_data_t* data) {
    static int16_t last_whole_count_raw{};
    if (!g_encoder) {
      return;
    }
    const std::optional<int16_t> curr_count_raw = g_encoder->count();
    if (!curr_count_raw) {
      return;
    }
    const int16_t diff = SignedMinus(*curr_count_raw, last_whole_count_raw);
    const int16_t pos = (diff + 1) / 4;
    const int16_t neg = (diff - 1) / 4;
    if (pos >= 1) {
      data->enc_diff = pos * g_encoder_dir;
      last_whole_count_raw += pos * 4;
      ESP_LOGD(TAG, "enc++ => %d", last_whole_count_raw);
    } else if (neg <= -1) {
      data->enc_diff = neg * g_encoder_dir;
      last_whole_count_raw += neg * 4;
      ESP_LOGD(TAG, "enc-- => %d", last_whole_count_raw);
    }
    const uint32_t button_raw = PollAdc();
    if (kButton2Low <= button_raw && button_raw < kButton2High) {
      ESP_LOGD(TAG, "btn2");
      data->state = LV_INDEV_STATE_PR;
    } else {
      data->state = LV_INDEV_STATE_REL;
    }
  };
  g_encoder_indev = lv_indev_drv_register(&driver);
  return g_encoder_indev ? ESP_OK : ESP_FAIL;
}

esp_err_t RegisterButtonDriver() {
  static lv_indev_drv_t driver;
  lv_indev_drv_init(&driver);
  driver.type = LV_INDEV_TYPE_KEYPAD;
  driver.read_cb = [](lv_indev_drv_t* drv, lv_indev_data_t* data) {
    const uint32_t button_raw = PollAdc();
    // TODO(summivox): state machine (only allow 1KRO)
    if (kButton1Low <= button_raw && button_raw < kButton1High) {
      ESP_LOGD(TAG, "btn1");
      data->key = LV_KEY_UP;
      data->state = LV_INDEV_STATE_PR;
    } else if (kButton3Low <= button_raw && button_raw < kButton3High) {
      ESP_LOGD(TAG, "btn3");
      data->key = LV_KEY_DOWN;
      data->state = LV_INDEV_STATE_PR;
    } else {
      data->state = LV_INDEV_STATE_REL;
    }
  };
  g_buttons_indev = lv_indev_drv_register(&driver);
  return g_buttons_indev ? ESP_OK : ESP_FAIL;
}

}  // namespace

lv_indev_t* g_encoder_indev{};
lv_indev_t* g_buttons_indev{};

int g_encoder_dir = +1;

esp_err_t RegisterLvglInputDrivers() {
  TRY(SetupAdc());

  TRY(RegisterEncoderDriver());
  // TRY(RegisterButtonDriver());
  return ESP_OK;
}

void SetInputGroup(lv_group_t* group) {
  CHECK(group != nullptr);
  if (g_encoder_indev) {
    lv_indev_set_group(g_encoder_indev, group);
  }
  if (g_buttons_indev) {
    lv_indev_set_group(g_buttons_indev, group);
  }
}

bool GetButtonState(int i) {
  const uint32_t button_raw = PollAdc();
  return (i == 1 && kButton1Low <= button_raw && button_raw < kButton1High) ||
         (i == 2 && kButton2Low <= button_raw && button_raw < kButton2High) ||
         (i == 3 && kButton3Low <= button_raw && button_raw < kButton3High);
}

}  // namespace ui
