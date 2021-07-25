// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"

namespace ui {
namespace view {

struct IdleScreen : public Screen {
  lv_obj_t* label_info;

  lv_obj_t* nav;
  lv_obj_t* btn_track;
  lv_obj_t* btn_review;
  lv_obj_t* btn_settings;

  LvEventHandler btn_track_click{};
  LvEventHandler btn_review_click{};
  LvEventHandler btn_settings_click{};

  virtual ~IdleScreen() = default;

  IdleScreen() {
    lv_obj_set_style_pad_row(screen, 2, 0);
    lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    // low-density dump of info (for now)
    label_info = lv_label_create(screen);
    lv_obj_set_size(label_info, LV_PCT(100), 32);
    lv_obj_add_style(label_info, &g_style->framed, 0);
    lv_obj_set_style_pad_left(label_info, 3, 0);

    nav = lv_obj_create(screen);
    lv_obj_set_size(nav, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(nav, 2, 0);
    lv_obj_set_style_border_width(nav, 0, 0);
    lv_obj_set_flex_flow(nav, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(nav, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    btn_track = lv_btn_create(nav);
    FixButton(btn_track);
#if 0
    {
      lv_obj_t* const label = lv_label_create(btn_track);
      lv_label_set_text_static(label, "Track");
      lv_obj_center(label);
    }
#else
    lv_obj_set_width(btn_track, 19);
    {
      lv_obj_t* const label = lv_label_create(btn_track);
      lv_label_set_text_static(label, (const char*)u8"\uf49b");
      lv_obj_set_width(label, LV_PCT(100));
      lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    }
#endif
    lv_group_add_obj(group, btn_track);
    LvListen(btn_track, LV_EVENT_CLICKED, btn_track_click);

    btn_review = lv_btn_create(nav);
    FixButton(btn_review);
#if 0
    {
      lv_obj_t* const label = lv_label_create(btn_review);
      lv_label_set_text_static(label, "Review");
      lv_obj_center(label);
    }
#else
    lv_obj_set_width(btn_review, 19);
    {
      lv_obj_t* const label = lv_label_create(btn_review);
      lv_label_set_text_static(label, (const char*)u8"\uf00b");
      lv_obj_set_width(label, LV_PCT(100));
      lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    }
#endif
    lv_group_add_obj(group, btn_review);
    LvListen(btn_review, LV_EVENT_CLICKED, btn_review_click);

    btn_settings = lv_btn_create(nav);
    FixButton(btn_settings);
    lv_obj_set_width(btn_settings, 19);
    {
      lv_obj_t* const label = lv_label_create(btn_settings);
      lv_label_set_text_static(label, (const char*)u8"\u2388");
      lv_obj_set_width(label, LV_PCT(100));
      lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    }
    lv_group_add_obj(group, btn_settings);
    LvListen(btn_settings, LV_EVENT_CLICKED, btn_settings_click);
  }

  void Render(const Model& model) override {
    static TickType_t last_time = xTaskGetTickCount();
    const TickType_t now = xTaskGetTickCount();
    const auto dt = SignedMinus(now, last_time);
    if (dt < pdMS_TO_TICKS(250)) {
      return;
    }
    last_time = now;

    const TimeZulu t = NowZulu();

    lv_label_set_text_fmt(label_info,
      (const char*)u8""
      "\uf970%02d" "\u2502"
      "%02d:%02d" "\u2502"
      "",
      model.gps ? (int)model.gps->num_sats : 0,
      t.tm_hour, t.tm_min
    );
  }
};

}  // namespace view
}  // namespace ui
