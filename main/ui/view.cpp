#include "ui/view.hpp"

#include <optional>

#include "driver/gpio.h"
#include "esp_log.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "lvgl.h"
#include "lvgl_helpers.h"

#include "common/logging.hpp"
#include "ui/model.hpp"

extern lv_font_t caecilia18;
extern lv_font_t caecilia22b;
extern lv_font_t consolas8;
extern lv_font_t consolas10;
extern lv_font_t iosevka10l;
extern lv_font_t iosevka12;
extern lv_font_t mononoki10;

namespace ui {

namespace {

constexpr char TAG[] = "ui/view";
constexpr int kRefreshPeriodMs = 50;

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

}  // namespace

TaskHandle_t g_view_task{};

esp_err_t ViewInit() {
  SetupDisplayDriver();
  return ESP_OK;
}

esp_err_t ViewStart() {
  return xTaskCreatePinnedToCore(ViewTask, "ui/view", 4096, nullptr, 2, &g_view_task, APP_CPU_NUM)
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
  TickType_t last_wake_time = xTaskGetTickCount();

  constexpr lv_color_t ON = LV_COLOR_BLACK;
  constexpr lv_color_t OFF = LV_COLOR_WHITE;

  lv_obj_t* screen = lv_disp_get_scr_act(NULL);

  lv_style_t small_text;
  lv_style_init(&small_text);
  lv_style_set_text_font(&small_text, LV_STATE_DEFAULT, &iosevka10l);
  lv_style_set_text_letter_space(&small_text, LV_STATE_DEFAULT, 1);

  lv_style_t big_text;
  lv_style_init(&big_text);
  lv_style_set_text_font(&big_text, LV_STATE_DEFAULT, &caecilia22b);
  lv_style_set_text_letter_space(&big_text, LV_STATE_DEFAULT, 1);

  lv_obj_t* label_clock = lv_label_create(screen, NULL);
  lv_obj_reset_style_list(label_clock, 0);
  lv_obj_add_style(label_clock, 0, &big_text);
  lv_label_set_text(label_clock, "--:--:--");
  lv_obj_align(label_clock, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_auto_realign(label_clock, true);

  lv_obj_t* label_latlong = lv_label_create(screen, NULL);
  lv_obj_reset_style_list(label_latlong, 0);
  lv_obj_add_style(label_latlong, 0, &small_text);
  lv_label_set_text(label_latlong, "+12.34567 -123.12345");
  lv_obj_align(label_latlong, NULL, LV_ALIGN_IN_TOP_MID, 0, 1);
  lv_obj_set_auto_realign(label_latlong, true);

  lv_obj_t* bar_file = lv_bar_create(screen, NULL);
  lv_obj_set_size(bar_file, 100, 4);
  lv_bar_set_range(bar_file, 0, CONFIG_MAX_LINES_PER_FILE);
  lv_obj_set_style_local_outline_width(bar_file, 0, LV_STATE_DEFAULT, 0);
  lv_obj_set_style_local_outline_color(bar_file, 0, LV_STATE_DEFAULT, ON);
  lv_bar_set_value(bar_file, 2500, LV_ANIM_OFF);
  lv_obj_align(bar_file, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -2);

  while (true) {
    if (const auto& g = g_model.gps) {
      lv_label_set_text(
          label_clock, fmt::format("{:02}:{:02}:{:02}", g->hour, g->minute, g->second).c_str());
      lv_label_set_text(
          label_latlong, fmt::format("{:+09.5f} {:+010.5f}", g->latitude, g->longitude).c_str());
    }
    lv_bar_set_value(bar_file, g_model.logger_lines, LV_ANIM_OFF);

    lv_task_handler();
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(kRefreshPeriodMs));
  }
}

}  // namespace ui
