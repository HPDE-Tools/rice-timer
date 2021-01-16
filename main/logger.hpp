#pragma once

#include <string>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

extern TaskHandle_t g_logger_task;

esp_err_t LoggerInit();
esp_err_t LoggerStart();
void LoggerStop();
esp_err_t SendToLogger(std::string&& moved_line, uint32_t timeout = portMAX_DELAY);
void LoggerTask(void* /*unused*/);

