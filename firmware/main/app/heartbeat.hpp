// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "freertos/FreeRTOS.h"

namespace app {

class Heartbeat;

extern std::unique_ptr<Heartbeat> g_heartbeat;

esp_err_t SetupHeartbeat();
esp_err_t StartHeartbeat();
void StopHeartbeat();

}  // namespace app
