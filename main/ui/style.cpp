// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/style.hpp"

#include <memory>

namespace ui {

std::unique_ptr<Style> g_style;

esp_err_t SetupStyle() {
  g_style = std::make_unique<Style>();
  return g_style ? ESP_OK : ESP_FAIL;
}

esp_err_t SetupTheme() {
  lv_theme_t* theme = lv_theme_mono_init(lv_disp_get_default(), /*dark bg*/ true, &cozette13);
  if (!theme) {
    return ESP_FAIL;
  }
  lv_disp_set_theme(lv_disp_get_default(), theme);
  return ESP_OK;
}

}  // namespace ui
