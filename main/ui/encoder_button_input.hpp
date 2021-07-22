// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "esp_err.h"
#include "lvgl.h"

namespace ui {

extern lv_indev_t* g_encoder_indev;
extern lv_indev_t* g_buttons_indev;

esp_err_t RegisterLvglInputDrivers();

bool GetButtonState(int i);

}  // namespace ui
