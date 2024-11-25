// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "device/gps_daemon.hpp"

namespace app {

extern QueueHandle_t g_gps_uart_queue;
extern std::unique_ptr<io::UartLineReader> g_gps_line_reader;
extern std::unique_ptr<GpsDaemon> g_gpsd;

esp_err_t SetupGps();
esp_err_t StartGpsInstance();

}  // namespace app
