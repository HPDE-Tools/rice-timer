#pragma once

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern TaskHandle_t g_display_task;
extern char g_display_content[9];

esp_err_t DisplayInit();
esp_err_t DisplayStart();
void DisplayStop();
void DisplayTask(void* /*unused*/);
