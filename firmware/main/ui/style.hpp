// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "lvgl.h"

extern lv_font_t cozette13;
extern lv_font_t creep211;
extern lv_font_t haxor18;
extern lv_font_t liberation18bn;
extern lv_font_t pixerif16;
extern lv_font_t spleen24;

namespace ui {

struct Style {
  lv_style_t text_tiny = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_text_font(&s, &creep211);
    lv_style_set_text_letter_space(&s, 0);
    lv_style_set_text_line_space(&s, -1);
    return s;
  }();

  lv_style_t text_small = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_text_font(&s, &cozette13);
    lv_style_set_text_letter_space(&s, 0);
    lv_style_set_text_line_space(&s, -1);
    return s;
  }();

  lv_style_t text_serif = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_text_font(&s, &pixerif16);
    lv_style_set_text_letter_space(&s, 1);
    lv_style_set_text_line_space(&s, -2);
    return s;
  }();

  lv_style_t text_title = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_text_font(&s, &liberation18bn);
    lv_style_set_text_letter_space(&s, 0);
    lv_style_set_text_line_space(&s, -1);
    return s;
  }();

  lv_style_t text_big = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_text_font(&s, &haxor18);
    lv_style_set_text_letter_space(&s, 0);
    return s;
  }();

  lv_style_t table_cell_hr = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_pad_hor(&s, 2);
    lv_style_set_pad_ver(&s, 0);
    lv_style_set_border_side(&s, LV_BORDER_SIDE_TOP);
    return s;
  }();

  lv_style_t btn_normal = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_pad_hor(&s, 3);
    lv_style_set_pad_ver(&s, 2);
    lv_style_set_border_width(&s, 1);
    return s;
  }();
  lv_style_t btn_pressed = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_pad_hor(&s, 2);
    lv_style_set_pad_ver(&s, 1);
    lv_style_set_border_width(&s, 2);
    return s;
  }();
  lv_style_t btn_focused = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_outline_color(&s, lv_color_white());
    return s;
  }();

  lv_style_t framed = []() {
    lv_style_t s{};
    lv_style_init(&s);
    lv_style_set_border_width(&s, 1);
    lv_style_set_border_color(&s, lv_color_white());
    lv_style_set_border_post(&s, true);
    lv_style_set_pad_ver(&s, 1);
    lv_style_set_radius(&s, 4);
    return s;
  }();
};

extern std::unique_ptr<Style> g_style;

esp_err_t SetupStyle();
esp_err_t SetupTheme();

}  // namespace ui
