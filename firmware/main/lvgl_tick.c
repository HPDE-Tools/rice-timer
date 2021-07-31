// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "lvgl_tick.h"

#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"

uint32_t millis() { return pdTICKS_TO_MS(xTaskGetTickCount()); }
