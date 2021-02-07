// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#include "device/can.hpp"

namespace app {

extern std::unique_ptr<CanManager> g_can;

esp_err_t SetupCan();

}  // namespace app
