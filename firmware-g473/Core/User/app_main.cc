// Copyright (c) rice-timer authors
#include <cstdint>

#include "main.h"
#include "gpio.h"

#include "sensor_input.h"

extern "C" void app_main() {
  SensorInputSetup();
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
  HAL_Delay(500);
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
  HAL_Delay(500);

  SensorInputStart();
}
