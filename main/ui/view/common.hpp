// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cinttypes>

#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "app/device_id.hpp"
#include "common/logging.hpp"
#include "math/polyfill.hpp"
#include "ui/model.hpp"
#include "ui/style.hpp"

namespace ui {
namespace view {

constexpr char TAG[] = "ui/view";

constexpr lv_color_t kOn = LV_COLOR_BLACK;
constexpr lv_color_t kOff = LV_COLOR_WHITE;

template <typename TFloat>
constexpr char SignChar(TFloat t) {
  return t >= 0 ? '+' : '-';
}

}  // namespace view
}  // namespace ui
