// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "esp_err.h"
#include "lvgl.h"

namespace ui {

extern lv_indev_t* g_encoder_indev;
extern lv_indev_t* g_buttons_indev;

extern int g_encoder_dir;  // +1 or -1

esp_err_t RegisterLvglInputDrivers();
void SetInputGroup(lv_group_t* group);

bool GetButtonState(int i);

}  // namespace ui
