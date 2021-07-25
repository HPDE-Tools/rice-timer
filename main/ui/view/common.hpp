// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cinttypes>
#include <functional>

#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "app/device_id.hpp"
#include "common/macros.hpp"
#include "common/utils.hpp"
#include "math/polyfill.hpp"
#include "ui/model.hpp"
#include "ui/style.hpp"

namespace ui {
namespace view {

namespace {
constexpr char TAG[] = "ui/view";
}  // namespace

//////////////////////////////////////////////////////

template <typename TFloat>
constexpr char SignChar(TFloat t) {
  return t >= 0 ? '+' : '-';
}

constexpr char const* kCourseStrings[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW", "N"};

template <typename TFloat>
const char* CourseToString(TFloat course_deg) {
  if (0 <= course_deg && course_deg <= 360) {
    return kCourseStrings[(int)std::round(course_deg * TFloat{8.0 / 360.0})];
  }
  return "?";
}

////////////////////////////////////////////////////

using LvEventHandler = std::function<void(lv_event_t*)>;

inline void LvListen(lv_obj_t* obj, lv_event_code_t filter, LvEventHandler& handler) {
  lv_obj_add_event_cb(
      obj,
      [](lv_event_t* e) {
        LvEventHandler& handler = *reinterpret_cast<LvEventHandler*>(e->user_data);
        if (handler) {
          handler(e);
        }
      },
      filter,
      &handler);
}

void FixButton(lv_obj_t* obj) {
  lv_obj_add_style(obj, &g_style->btn_normal, LV_STATE_DEFAULT);
  lv_obj_add_style(obj, &g_style->btn_pressed, LV_STATE_PRESSED);
}

void MergeCell(lv_obj_t* table, uint16_t row, uint16_t col) {
  lv_table_add_cell_ctrl(table, row, col, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
}

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
