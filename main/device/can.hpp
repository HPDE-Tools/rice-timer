#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

extern TaskHandle_t g_can_task;

esp_err_t CanInit();
esp_err_t CanStart();
void CanStop();
void CanTask(void* /*unused*/);
