#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

extern TaskHandle_t g_imu_task;

esp_err_t ImuInit();
esp_err_t ImuStart();
void ImuStop();
void ImuTask(void* /*unused*/);

