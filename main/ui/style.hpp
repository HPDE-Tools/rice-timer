// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "lvgl.h"

extern lv_font_t iosevka10l;
extern lv_font_t iosevka12;
extern lv_font_t liberation8n;
extern lv_font_t liberation18bn;
extern lv_font_t liberation22bn;
extern lv_font_t mononoki10;
extern lv_font_t mononoki22;
extern lv_font_t notomono8;
extern lv_font_t notomono9;

namespace ui {

struct Style {
  lv_style_t text_tiny = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, &notomono8);
    lv_style_set_text_letter_space(&s, 1);
    lv_style_set_text_line_space(&s, -1);
    return s;
  }();

  lv_style_t text_small = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, &iosevka10l);
    lv_style_set_text_letter_space(&s, 1);
    lv_style_set_text_line_space(&s, -2);
    return s;
  }();

  lv_style_t text_medium = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, &iosevka12);
    lv_style_set_text_letter_space(&s, 1);
    lv_style_set_text_line_space(&s, -2);
    return s;
  }();

  lv_style_t text_big = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, &mononoki22);
    lv_style_set_text_letter_space(&s, 1);
    return s;
  }();

  lv_style_t container_hr_bottom = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_pad_bottom(&s, 1);
    lv_style_set_border_width(&s, 1);
    lv_style_set_border_side(&s, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&s, 0);
    return s;
  }();

  lv_style_t container_hr_top = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_pad_top(&s, 1);
    lv_style_set_border_width(&s, 1);
    lv_style_set_border_side(&s, LV_BORDER_SIDE_TOP);
    lv_style_set_radius(&s, 0);
    return s;
  }();
};

extern std::unique_ptr<Style> g_style;

esp_err_t SetupStyle();
esp_err_t SetupTheme();

}  // namespace ui
