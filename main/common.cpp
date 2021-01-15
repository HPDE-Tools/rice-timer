#include "common.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

namespace {

SemaphoreHandle_t g_i2c_mutex{};

}  // namespace

void InitI2cMutex() { g_i2c_mutex = xSemaphoreCreateMutex(); }
void TakeI2cMutex() { xSemaphoreTake(g_i2c_mutex, portMAX_DELAY); }
void ReleaseI2cMutex() { xSemaphoreGive(g_i2c_mutex); }
