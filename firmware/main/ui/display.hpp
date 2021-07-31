// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"

#include "device/oled_ssd1309.hpp"

namespace ui {

extern std::unique_ptr<OledSsd1309> g_oled;

esp_err_t SetupOled();

}  // namespace ui
