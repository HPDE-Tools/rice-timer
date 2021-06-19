// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "esp_err.h"
#include "lvgl.h"

namespace app {

extern lv_indev_t* g_encoder_indev;
extern lv_indev_t* g_buttons_indev;

esp_err_t RegisterLvglInputDrivers();

}  // namespace app
