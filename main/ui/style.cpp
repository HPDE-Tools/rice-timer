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

}  // namespace ui
