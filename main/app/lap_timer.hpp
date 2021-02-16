// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "minmea.h"

#include "common/times.hpp"
#include "map/car_pose.hpp"

namespace app {

class LapTimer;
extern std::unique_ptr<LapTimer> g_lap_timer;

TaskHandle_t GetLapTimerTask();
esp_err_t SetupLapTimer();
esp_err_t StartLapTimerTask();
void ResetLapTimer();
void UpdateGps(const minmea_sentence_rmc& rmc);

}  // namespace app
