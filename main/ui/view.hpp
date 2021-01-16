#pragma once

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace ui {

extern TaskHandle_t g_view_task;

esp_err_t ViewInit();
esp_err_t ViewStart();
void ViewStop();
void ViewTask(void* /*unused*/);

}  // namespace ui
