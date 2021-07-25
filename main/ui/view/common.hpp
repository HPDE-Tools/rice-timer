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
#include "common/times.hpp"
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
constexpr char8_t const* kCourseArrows[] = {
    u8"\u2191",
    u8"\u2197",
    u8"\u2192",
    u8"\u2198",
    u8"\u2193",
    u8"\u2199",
    u8"\u2190",
    u8"\u2196",
    u8"\u2191",
};

template <typename TFloat>
int CourseToBin(TFloat course_deg) {
  if (0 <= course_deg && course_deg <= 360) {
    return (int)std::round(course_deg * TFloat{8.0 / 360.0});
  }
  return -1;
}

template <typename TFloat>
const char* CourseToString(TFloat course_deg) {
  const int i = CourseToBin(course_deg);
  return (0 <= i && i <= 8) ? kCourseStrings[i] : "?";
}

template <typename TFloat>
const char* CourseToArrow(TFloat course_deg) {
  const int i = CourseToBin(course_deg);
  return (0 <= i && i <= 8) ? kCourseArrows[i] : u8"\u2218";
}

constexpr char8_t const* kSpinner6[] = {
    u8"\u2801",
    u8"\u2802",
    u8"\u2804",
    u8"\u2820",
    u8"\u2810",
    u8"\u2808",
};

#define UTF8 (const char*)u8""

#define EMSP13 u8"\u2004"
#define THINSP u8"\u2009"

#define SYM_YES u8"\u2713"
#define SYM_NO u8"\u2717"
#define SYM_PIPE u8"\u2502"

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

}  // namespace view
}  // namespace ui
