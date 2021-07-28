// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"
#include "ui/view/screen.hpp"

namespace ui {
namespace view {

struct TrackSelScreen : public Screen {
  lv_obj_t* switch_auto;
  lv_obj_t* dropdown_sort;

  lv_obj_t* list_tracks;

  LvEventHandler btn_refresh_click{};
  LvEventHandler btn_go_click{};

  virtual ~TrackSelScreen() = default;
  TrackSelScreen() {
    lv_obj_set_style_pad_row(screen, 2, 0);
    lv_obj_set_style_pad_hor(screen, 2, 0);
    lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

    switch_auto = lv_btn_create(screen);
    FixButton(switch_auto);
    lv_obj_set_height(switch_auto, 15);
    lv_obj_add_flag(switch_auto, LV_OBJ_FLAG_CHECKABLE);
    {
      lv_obj_t* label = lv_label_create(switch_auto);
      lv_obj_add_style(label, &g_style->text_tiny, 0);
      lv_label_set_text_static(label, "Auto");
      lv_obj_center(label);
    }
    static LvEventHandler switch_auto_changed = [this](lv_event_t* e) {
      const bool checked = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
      ESP_LOGI(TAG, "track auto sel: %d", (int)checked);
      // TODO
    };
    LvListen(switch_auto, LV_EVENT_VALUE_CHANGED, switch_auto_changed);
    lv_group_add_obj(group, switch_auto);

    dropdown_sort = lv_dropdown_create(screen);
    lv_obj_set_height(dropdown_sort, 15);
    lv_obj_set_flex_grow(dropdown_sort, 1);
    lv_obj_set_style_pad_ver(dropdown_sort, 2, 0);
    lv_obj_set_style_border_width(dropdown_sort, 1, LV_STATE_PRESSED);
    lv_obj_add_style(dropdown_sort, &g_style->text_tiny, 0);
    lv_group_add_obj(group, dropdown_sort);

    lv_obj_t* btn_refresh = lv_btn_create(screen);
    FixButton(btn_refresh);
    lv_obj_set_size(btn_refresh, 15, 15);
    {
      lv_obj_t* label = lv_label_create(btn_refresh);
      lv_obj_add_style(label, &g_style->text_tiny, 0);
      lv_label_set_text_static(label, UTF8 "\uf021");
      lv_obj_center(label);
    }
    LvListen(btn_refresh, LV_EVENT_CLICKED, btn_refresh_click);
    lv_group_add_obj(group, btn_refresh);

    lv_obj_t* btn_go = lv_btn_create(screen);
    FixButton(btn_go);
    lv_obj_set_height(btn_go, 15);
    {
      lv_obj_t* label = lv_label_create(btn_go);
      lv_obj_add_style(label, &g_style->text_tiny, 0);
      lv_label_set_text_static(label, "GO");
      lv_obj_center(label);
    }
    LvListen(btn_go, LV_EVENT_CLICKED, btn_go_click);
    lv_group_add_obj(group, btn_go);

    list_tracks = lv_list_create(screen);
    lv_obj_set_size(list_tracks, LV_PCT(100), 37);
    lv_obj_add_flag(list_tracks, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_obj_set_style_pad_all(list_tracks, 2, 0);
    lv_obj_set_style_pad_row(list_tracks, 0, 0);
    lv_obj_set_style_pad_ver(list_tracks, 1, LV_PART_ITEMS);
    lv_obj_add_style(list_tracks, &g_style->framed, 0);
    lv_obj_add_style(list_tracks, &g_style->text_tiny, 0);
    {
      lv_obj_t* btn = lv_list_add_btn(list_tracks, (const char*)kCourseArrows[3], "Laguna Seca");
      lv_obj_set_style_pad_all(btn, 1, 0);
      lv_group_add_obj(group, btn);
    }
    {
      lv_obj_t* btn = lv_list_add_btn(list_tracks, (const char*)kCourseArrows[7], "Thunderhill");
      lv_obj_set_style_pad_all(btn, 1, 0);
      lv_group_add_obj(group, btn);
    }
    {
      lv_obj_t* btn = lv_list_add_btn(list_tracks, (const char*)kCourseArrows[7], "Sonoma Raceway");
      lv_obj_set_style_pad_all(btn, 1, 0);
      lv_group_add_obj(group, btn);
    }
    {
      lv_obj_t* btn =
          lv_list_add_btn(list_tracks, (const char*)kCourseArrows[2], UTF8 "Nürburgring");
      lv_obj_set_style_pad_all(btn, 1, 0);
      lv_group_add_obj(group, btn);
    }
    // lv_group_add_obj(group, list_tracks);
  }

  void Render(const Model& model) override {
    // TODO
  }
};

}  // namespace view
}  // namespace ui
