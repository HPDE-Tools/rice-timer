#include "common.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

namespace {

SemaphoreHandle_t g_i2c_mutex{};

}  // namespace

void InitArduinoMutex() { g_i2c_mutex = xSemaphoreCreateMutex(); }
void TakeArduinoMutex() { xSemaphoreTake(g_i2c_mutex, portMAX_DELAY); }
void ReleaseArduinoMutex() { xSemaphoreGive(g_i2c_mutex); }
