// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/view.hpp"

#include <optional>

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "lvgl.h"
#include "lvgl_helpers.h"

#include "common/logging.hpp"
#include "common/times.hpp"
#include "ui/model.hpp"

extern lv_font_t iosevka10l;
extern lv_font_t iosevka12;
extern lv_font_t mononoki10;
extern lv_font_t mononoki22;

namespace ui {

namespace {

constexpr char TAG[] = "ui/view";
constexpr int kRefreshPeriodMs = 100;

constexpr uint8_t outer_x[] = {62, 61, 58, 55, 51, 46, 40, 34, 28, 22, 16, 11, 7,  4,  1,  0,
                               0,  1,  4,  7,  11, 16, 22, 28, 34, 40, 46, 51, 55, 58, 61, 62};
constexpr uint8_t outer_y[] = {34, 40, 46, 51, 55, 58, 61, 62, 62, 61, 58, 55, 51, 46, 40, 34,
                               28, 22, 16, 11, 7,  4,  1,  0,  0,  1,  4,  7,  11, 16, 22, 28};
constexpr uint8_t inner_x[] = {51, 49, 45, 40, 34, 28, 22, 17, 13, 11,
                               11, 13, 17, 22, 28, 34, 40, 45, 49, 51};
constexpr uint8_t inner_y[] = {34, 40, 45, 49, 51, 51, 49, 45, 40, 34,
                               28, 22, 17, 13, 11, 11, 13, 17, 22, 28};

esp_err_t SetupDisplayDriver() {
  lv_init();
  lvgl_driver_init();

  static lv_color_t buf1[DISP_BUF_SIZE];
  static lv_disp_buf_t disp_buf;
  lv_disp_buf_init(&disp_buf, buf1, /*buf2*/ nullptr, DISP_BUF_SIZE);

  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = disp_driver_flush;
  disp_drv.rounder_cb = disp_driver_rounder;
  disp_drv.set_px_cb = disp_driver_set_px;
  disp_drv.buffer = &disp_buf;
  if (lv_disp_drv_register(&disp_drv) == nullptr) {
    return ESP_FAIL;
  }

  return ESP_OK;
}

uint8_t ReadButtons(uint8_t addr_7bit) {
  constexpr uint8_t kRequest[] = {0x02, 0x04, 0x00, 0x04};
  {
    i2c_cmd_handle_t txn = i2c_cmd_link_create();
    OK_OR_RETURN(i2c_master_start(txn), 0);
    OK_OR_RETURN(i2c_master_write_byte(txn, addr_7bit << 1 | I2C_MASTER_WRITE, true), 0);
    OK_OR_RETURN(i2c_master_write(txn, kRequest, sizeof(kRequest), true), 0);
    OK_OR_RETURN(i2c_master_stop(txn), 0);
    OK_OR_RETURN(i2c_master_cmd_begin(I2C_NUM_0, txn, 10), 0);
    i2c_cmd_link_delete(txn);
  }
  vTaskDelay(pdMS_TO_TICKS(2));
  uint8_t result[5];
  {
    i2c_cmd_handle_t txn = i2c_cmd_link_create();
    OK_OR_RETURN(i2c_master_start(txn), 0);
    OK_OR_RETURN(i2c_master_write_byte(txn, addr_7bit << 1 | I2C_MASTER_READ, true), 0);
    OK_OR_RETURN(i2c_master_read(txn, result, sizeof(result), I2C_MASTER_ACK), 0);
    OK_OR_RETURN(i2c_master_stop(txn), 0);
    OK_OR_RETURN(i2c_master_cmd_begin(I2C_NUM_0, txn, 10), 0);
    i2c_cmd_link_delete(txn);
  }
  return result[2];
}

}  // namespace

TaskHandle_t g_view_task{};

esp_err_t ViewInit() {
  SetupDisplayDriver();
  return ESP_OK;
}

esp_err_t ViewStart() {
  return xTaskCreatePinnedToCore(ViewTask, "ui/view", 6000, nullptr, 2, &g_view_task, APP_CPU_NUM)
             ? ESP_OK
             : ESP_FAIL;
}

void ViewStop() {
  if (g_view_task) {
    vTaskDelete(g_view_task);
    g_view_task = nullptr;
  }
}

void ViewTask(void* /*unused*/) {
  constexpr lv_color_t kOn = LV_COLOR_BLACK;
  constexpr lv_color_t kOff = LV_COLOR_WHITE;

  TickType_t last_wake_time = xTaskGetTickCount();

  // Screen 1: Dashboard
  static lv_obj_t* screen1 = lv_disp_get_scr_act(nullptr);

  lv_style_t small_text;
  lv_style_init(&small_text);
  lv_style_set_text_font(&small_text, LV_STATE_DEFAULT, &iosevka10l);
  lv_style_set_text_letter_space(&small_text, LV_STATE_DEFAULT, 1);

  static lv_style_t big_text;
  lv_style_init(&big_text);
  lv_style_set_text_font(&big_text, LV_STATE_DEFAULT, &mononoki22);
  lv_style_set_text_letter_space(&big_text, LV_STATE_DEFAULT, 1);

  static lv_draw_line_dsc_t solid_line;
  lv_draw_line_dsc_init(&solid_line);
  solid_line.opa = LV_OPA_100;
  solid_line.color = kOn;
  solid_line.width = 1;

  static lv_draw_line_dsc_t dotted_line;
  lv_draw_line_dsc_init(&dotted_line);
  solid_line.opa = LV_OPA_100;
  dotted_line.color = kOn;
  dotted_line.width = 1;
  dotted_line.dash_width = 1;
  dotted_line.dash_gap = 9;

  static lv_obj_t* label_latlong = lv_label_create(screen1, nullptr);
  lv_obj_reset_style_list(label_latlong, 0);
  lv_obj_add_style(label_latlong, 0, &small_text);
  lv_label_set_text(label_latlong, "+12.34567 -123.12345");
  lv_obj_align(label_latlong, nullptr, LV_ALIGN_IN_TOP_MID, 0, 1);
  lv_obj_set_auto_realign(label_latlong, true);

  static lv_obj_t* label_clock = lv_label_create(screen1, nullptr);
  lv_obj_reset_style_list(label_clock, 0);
  lv_obj_add_style(label_clock, 0, &big_text);
  lv_label_set_text(label_clock, "12:34:56");
  lv_obj_align(label_clock, label_latlong, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_obj_set_auto_realign(label_clock, true);

  static lv_obj_t* bar_file = lv_bar_create(screen1, nullptr);
  lv_obj_set_size(bar_file, 100, 4);
  lv_bar_set_range(bar_file, 0, CONFIG_MAX_LINES_PER_FILE);
  lv_obj_set_style_local_outline_width(bar_file, 0, LV_STATE_DEFAULT, 0);
  // lv_obj_set_style_local_outline_color(bar_file, 0, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  lv_bar_set_value(bar_file, 2500, LV_ANIM_OFF);
  lv_obj_align(bar_file, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, -1);

  static lv_obj_t* label_imu = lv_label_create(screen1, label_latlong);
  lv_obj_align(label_imu, label_clock, LV_ALIGN_OUT_BOTTOM_MID, 0, -2);

  // Screen 2: IMU G-circle in the X-Y plane
  static lv_obj_t* screen2 = lv_obj_create(nullptr, nullptr);

  static lv_obj_t* canvas_imu = lv_canvas_create(screen2, nullptr);
  lv_obj_set_size(canvas_imu, 63, 63);
  lv_obj_align(canvas_imu, nullptr, LV_ALIGN_CENTER, 0, 0);
  static uint8_t canvas_buf[LV_CANVAS_BUF_SIZE_INDEXED_1BIT(63, 63)];
  lv_canvas_set_buffer(canvas_imu, canvas_buf, 63, 63, LV_IMG_CF_INDEXED_1BIT);
  lv_canvas_set_palette(canvas_imu, 0, LV_COLOR_BLACK);
  lv_canvas_set_palette(canvas_imu, 1, LV_COLOR_WHITE);

  // Screen 3: Lap Timing (currently fully off)
  static lv_obj_t* screen3 = lv_obj_create(nullptr, nullptr);

  while (true) {
    static uint8_t last_buttons = 0;
    const uint8_t buttons = ReadButtons(0b0000010);
    const uint8_t click = last_buttons & ~buttons;
    if (click & 0b001) {
      lv_scr_load(screen1);
    } else if (click & 0b010) {
      lv_scr_load(screen2);
    } else if (click & 0b100) {
      lv_scr_load(screen3);
    }
    last_buttons = buttons;
    ESP_LOGD(TAG, "buttons: %d; click: %d", buttons, click);

    const TimeUnixWithUs begin = NowUnixWithUs();

    if (const auto& gps = g_model.gps) {
      lv_label_set_text_fmt(label_clock, "%02d:%02d:%02d", gps->hour, gps->minute, gps->second);
      lv_label_set_text_fmt(label_latlong, "%+09.5f %+010.5f", gps->latitude, gps->longitude);
    } else {
      lv_label_set_text(label_clock, "--:--:--");
      lv_label_set_text(label_latlong, "");
    }
    lv_bar_set_value(bar_file, g_model.logger_lines, LV_ANIM_OFF);
    if (const auto& imu = g_model.imu) {
      lv_label_set_text_fmt(label_imu, "%+6.3f %+6.3f %+6.3f", imu->ax, imu->ay, imu->az);
      lv_canvas_fill_bg(canvas_imu, kOff, LV_OPA_100);
      for (int x = 0; x <= 63; x += 3) {
        lv_canvas_set_px(canvas_imu, x, 31, kOn);
      }
      for (int y = 0; y <= 63; y += 3) {
        lv_canvas_set_px(canvas_imu, 31, y, kOn);
      }
      for (int i = 0; i < sizeof(inner_x) / sizeof(inner_x[0]); i++) {
        lv_canvas_set_px(canvas_imu, inner_x[i], inner_y[i], kOn);
      }
      for (int i = 0; i < sizeof(outer_x) / sizeof(outer_x[0]); i++) {
        lv_canvas_set_px(canvas_imu, outer_x[i], outer_y[i], kOn);
      }
      const int ax_p = std::round(imu->ax * 31 / 1.5 + 31);
      const int ay_p = std::round(imu->ay * 31 / 1.5 + 31);
      for (int z = -4; z <= 4; z++) {
        lv_canvas_set_px(canvas_imu, std::clamp(ax_p - z, 0, 62), std::clamp(ay_p - z, 0, 62), kOn);
        lv_canvas_set_px(canvas_imu, std::clamp(ax_p - z, 0, 62), std::clamp(ay_p + z, 0, 62), kOn);
      }
    } else {
      lv_label_set_text(label_imu, "");
    }
    const TimeUnixWithUs end_update = NowUnixWithUs();

    lv_task_handler();
    const TimeUnixWithUs end_render = NowUnixWithUs();
    ESP_LOGD(TAG, "update: %lld; all: %lld", end_update - begin, end_render - begin);

    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(kRefreshPeriodMs));
  }
}

}  // namespace ui
