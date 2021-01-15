#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

extern TaskHandle_t g_gps_task;

esp_err_t GpsInit();
esp_err_t GpsStart();
void GpsStop();
void GpsTask(void* /*unused*/);
