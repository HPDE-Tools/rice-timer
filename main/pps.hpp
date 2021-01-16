#pragma once

#include <optional>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

extern TaskHandle_t g_pps_task;
extern std::optional<uint32_t> g_pps_latest_capture;

esp_err_t PpsInit();
esp_err_t PpsStart();
void PpsStop();
void PpsTask(void* /*unused*/);
