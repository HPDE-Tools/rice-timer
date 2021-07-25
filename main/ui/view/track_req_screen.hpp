// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"

namespace ui {
namespace view {

struct TrackReqScreen : public Screen {
  static constexpr char8_t kGpsFixYes[] = u8"GPS Fix: \u2713";
  static constexpr char8_t kGpsFixNo[] = u8"GPS Fix: \u2715";
  static constexpr char8_t kSdYes[] = u8"SD Card: \u2713";
  static constexpr char8_t kSdNo[] = u8"SD Card: \u2715";

  lv_obj_t* label_req_gps;
  lv_obj_t* label_req_sd;
  lv_obj_t* label_countdown;

  LvEventHandler on_success{};

  virtual ~TrackReqScreen() = default;
  TrackReqScreen() {
    lv_obj_set_style_pad_row(screen, 2, 0);
    lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    {
      lv_obj_t* title = lv_label_create(screen);
      lv_obj_add_style(title, &g_style->text_tiny, 0);
      lv_label_set_text_static(title, "Track mode needs:");
    }

    label_req_gps = lv_label_create(screen);
    lv_obj_set_width(label_req_gps, LV_PCT(90));
    lv_obj_add_style(label_req_gps, &g_style->framed, 0);
    lv_obj_set_style_pad_left(label_req_gps, 3, 0);

    label_req_sd = lv_label_create(screen);
    lv_obj_set_width(label_req_sd, LV_PCT(90));
    lv_obj_add_style(label_req_sd, &g_style->framed, 0);
    lv_obj_set_style_pad_left(label_req_sd, 3, 0);
  }

  void Render(const Model& model) override {
    lv_label_set_text_static(label_req_gps, (const char*)(model.gps ? kGpsFixYes : kGpsFixNo));
    lv_label_set_text_static(label_req_sd, (const char*)(model.sd_card ? kSdYes : kSdNo));
    if (model.gps && model.sd_card) {
      if (on_success) {
        on_success(nullptr);
      }
    }
  }
};

}  // namespace view
}  // namespace ui
