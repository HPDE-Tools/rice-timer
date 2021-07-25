// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"

namespace ui {
namespace view {

struct IdleScreen : public Screen {
  lv_obj_t* nav;
  lv_obj_t* btn_track;
  lv_obj_t* btn_review;
  lv_obj_t* btn_settings;

  LvEventHandler btn_track_click{};
  LvEventHandler btn_review_click{};
  LvEventHandler btn_settings_click{};

  virtual ~IdleScreen() = default;

  IdleScreen() {
    ESP_LOGI(TAG, "screen: 0x%08x", (uintptr_t)screen);
    nav = lv_obj_create(screen);
    lv_obj_set_size(nav, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_align(nav, LV_ALIGN_BOTTOM_MID, 0, -5);
    lv_obj_set_style_border_width(nav, 0, 0);
    lv_obj_set_flex_flow(nav, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(nav, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    btn_track = lv_btn_create(nav);
    FixButton(btn_track);
    {
      lv_obj_t* const label = lv_label_create(btn_track);
      lv_label_set_text_static(label, "Track");
      lv_obj_center(label);
    }
    lv_group_add_obj(group, btn_track);
    LvListen(btn_track, LV_EVENT_CLICKED, btn_track_click);

    btn_review = lv_btn_create(nav);
    FixButton(btn_review);
    {
      lv_obj_t* const label = lv_label_create(btn_review);
      lv_label_set_text_static(label, "Review");
      lv_obj_center(label);
    }
    lv_group_add_obj(group, btn_review);
    LvListen(btn_review, LV_EVENT_CLICKED, btn_review_click);

    btn_settings = lv_btn_create(nav);
    FixButton(btn_settings);
    lv_obj_set_width(btn_settings, 18);
#if 1
    {
      lv_obj_t* const label = lv_label_create(btn_settings);
      lv_label_set_text_static(label, (const char*)u8"\u2388");
      lv_obj_set_width(label, LV_PCT(100));
      lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    }
#else
    {
      lv_obj_t* const img = lv_img_create(btn_settings);
      lv_img_set_src(img, u8"\u2388");
      lv_obj_center(img);
    }
#endif
    lv_group_add_obj(group, btn_settings);
    LvListen(btn_settings, LV_EVENT_CLICKED, btn_settings_click);
  }

  void Render(const Model& model) override {}
};

}  // namespace view
}  // namespace ui
