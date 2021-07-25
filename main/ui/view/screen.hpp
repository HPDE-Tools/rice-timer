// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "ui/view/common.hpp"

namespace ui {
namespace view {

struct Screen {
  lv_obj_t* screen;
  lv_group_t* group;

  virtual ~Screen() {
    lv_group_del(group);
    lv_obj_del(screen);
  }

  Screen() : screen(lv_obj_create(nullptr)), group(lv_group_create()) {}

  Screen* Load() {
    ESP_LOGI(TAG, "loading: 0x%08x", (uintptr_t)screen);
    lv_scr_load(screen);
    SetInputGroup(group);
    return this;
  }
  Screen* LoadAnim(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del) {
    ESP_LOGI(TAG, "loading: 0x%08x", (uintptr_t)screen);
    lv_scr_load_anim(screen, anim_type, time, delay, auto_del);
    SetInputGroup(group);
    return this;
  }

  virtual void Render(const Model& model) = 0;
};

}  // namespace view
}  // namespace ui
