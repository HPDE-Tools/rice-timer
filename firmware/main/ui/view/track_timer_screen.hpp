// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"
#include "ui/view/screen.hpp"

namespace ui {
namespace view {

struct TrackTimerScreen : public Screen {
  static constexpr char kCurrLapPlaceholder[] = "   |--:--.-";
  virtual ~TrackTimerScreen() = default;

  lv_obj_t* label_info;
  lv_obj_t* label_curr_lap;
  lv_obj_t* label_last_lap;
  lv_obj_t* label_best_lap;

  TrackTimerScreen() {
    lv_obj_set_style_pad_row(screen, 1, 0);
    lv_obj_set_style_pad_column(screen, 2, 0);
    lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    label_info = lv_label_create(screen);
    lv_label_set_text_static(label_info, "");

    label_curr_lap = lv_label_create(screen);
    lv_obj_add_flag(label_curr_lap, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_obj_add_style(label_curr_lap, &g_style->text_big, LV_PART_MAIN);
    lv_label_set_text_static(label_curr_lap, kCurrLapPlaceholder);

    label_last_lap = lv_label_create(screen);
    lv_obj_add_flag(label_last_lap, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_label_set_text_static(label_last_lap, "last");

    label_best_lap = lv_label_create(screen);
    lv_obj_add_flag(label_best_lap, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_label_set_text_static(label_best_lap, "best");
  }

  virtual void Render(const Model& model) {
    const TimeUnixWithUs now = NowUnixWithUs();
    const int64_t now_ms = ToMilliseconds(now);
    const TimeZulu now_cal = ToZulu(now);

    std::string logger_status{};
    if (model.sd_card) {
      logger_status = model.is_logger_running ? UTF8 "\uf111" EMSP13 : UTF8 "\uf04c" EMSP13;
      if (model.logger) {
        logger_status += std::to_string(model.logger->session_id);
      }
    }

    lv_label_set_text_fmt(
        label_info,
        "%02d:%02d:%02d %s",
        now_cal.tm_hour,
        now_cal.tm_min,
        now_cal.tm_sec,
        logger_status.c_str());

    if (!model.lap_timer) {
      lv_label_set_text_static(label_curr_lap, kCurrLapPlaceholder);
      lv_label_set_text_static(label_last_lap, "last");
      lv_label_set_text_static(label_best_lap, "best");
      return;
    }

    const int lap_counter = model.lap_timer->num_complete_laps + 1;
    if (model.lap_timer->curr_lap_start_timestamp_ms) {
      int32_t diff = now_ms - *model.lap_timer->curr_lap_start_timestamp_ms;
      diff /= 100;
      const int ds = diff % 10;
      diff /= 10;
      const int sec = diff % 60;
      diff /= 60;
      const int min = std::min(diff, 99);
      lv_label_set_text_fmt(label_curr_lap, "%3d|%2d:%02d.%d", lap_counter, min, sec, ds);
    } else {
      lv_label_set_text_static(label_curr_lap, kCurrLapPlaceholder);
    }
    if (model.lap_timer->last_lap_duration_ms) {
      int32_t duration = *model.lap_timer->last_lap_duration_ms;
      const int ms = duration % 1000;
      duration /= 1000;
      const int sec = duration % 60;
      duration /= 60;
      const int min = std::min(duration, 99);
      lv_label_set_text_fmt(label_last_lap, "last %2d:%02d.%03d", min, sec, ms);
    } else {
      lv_label_set_text_static(label_last_lap, "last");
    }
    if (model.lap_timer->min_lap_index >= 0) {
      int32_t duration = model.lap_timer->min_lap_duration_ms;
      const int ms = duration % 1000;
      duration /= 1000;
      const int sec = duration % 60;
      duration /= 60;
      const int min = std::min(duration, 99);
      lv_label_set_text_fmt(
          label_best_lap,
          "best %2d:%02d.%03d #%d",
          min,
          sec,
          ms,
          model.lap_timer->min_lap_index + 1);
    } else {
      lv_label_set_text_static(label_best_lap, "best");
    }
  }
};

}  // namespace view
}  // namespace ui
