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
    lv_style_set_text_font(&s, LV_STATE_DEFAULT, &notomono8);
    lv_style_set_text_letter_space(&s, LV_STATE_DEFAULT, 1);
    lv_style_set_text_line_space(&s, LV_STATE_DEFAULT, -1);
    return s;
  }();

  lv_style_t text_tiny_icon = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, LV_STATE_DEFAULT, &lv_font_montserrat_8);
    lv_style_set_text_letter_space(&s, LV_STATE_DEFAULT, 1);
    return s;
  }();

  lv_style_t text_small = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, LV_STATE_DEFAULT, &iosevka10l);
    lv_style_set_text_letter_space(&s, LV_STATE_DEFAULT, 1);
    lv_style_set_text_line_space(&s, LV_STATE_DEFAULT, -2);
    return s;
  }();

  lv_style_t text_small_icon = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, LV_STATE_DEFAULT, &lv_font_montserrat_10);
    lv_style_set_text_letter_space(&s, LV_STATE_DEFAULT, 1);
    return s;
  }();

  lv_style_t text_medium = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, LV_STATE_DEFAULT, &iosevka12);
    lv_style_set_text_letter_space(&s, LV_STATE_DEFAULT, 1);
    lv_style_set_text_line_space(&s, LV_STATE_DEFAULT, -2);
    return s;
  }();

  lv_style_t text_big = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_text_font(&s, LV_STATE_DEFAULT, &mononoki22);
    lv_style_set_text_letter_space(&s, LV_STATE_DEFAULT, 1);
    return s;
  }();

  lv_style_t container_hr_bottom = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_pad_bottom(&s, LV_STATE_DEFAULT, 1);
    lv_style_set_border_width(&s, LV_STATE_DEFAULT, 1);
    lv_style_set_border_side(&s, LV_STATE_DEFAULT, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&s, LV_STATE_DEFAULT, 0);
    return s;
  }();

  lv_style_t container_hr_top = []() {
    lv_style_t s;
    lv_style_init(&s);
    lv_style_set_pad_top(&s, LV_STATE_DEFAULT, 1);
    lv_style_set_border_width(&s, LV_STATE_DEFAULT, 1);
    lv_style_set_border_side(&s, LV_STATE_DEFAULT, LV_BORDER_SIDE_TOP);
    lv_style_set_radius(&s, LV_STATE_DEFAULT, 0);
    return s;
  }();
};

extern std::unique_ptr<Style> g_style;

esp_err_t SetupStyle();

}  // namespace ui
