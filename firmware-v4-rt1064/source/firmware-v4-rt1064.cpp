// Copyright 2024 summivox@gmail.com (Yin Zhong)

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <random>

#include "board.h"
#include "clock_config.h"
#include "FreeRTOS.h"
#include "fsl_clock.h"
#include "fsl_debug_console.h"
#include "fsl_flexio.h"
#include "fsl_semc.h"
#include "MIMXRT1064.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "task.h"

#include "neopixel_test.hpp"
#include "sdram_config.hpp"
#include "sdram_test.hpp"


int main(void) {
  BOARD_ConfigMPU();
  BOARD_InitBootClocks();
  BOARD_InitBootPins();
  BOARD_InitPeripherals();
  BOARD_InitDebugConsole();
  if (const status_t status = SdramInit(); status != kStatus_Success) {
    printf("BOARD_InitSEMC2 fail: %d", static_cast<int>(status));
  }

  printf("\r\n\r\n=== RiceTimer v4 Firmware Build: %s %s ===\r\n\r\n", __DATE__, __TIME__);

  TestSdramSeqWrite4B();
  TestSdramRandomAccess4B();

  printf("\r\n== Start FreeRTOS ==\r\n\r\n");

  // NeopixelTaskInit();
  vTaskStartScheduler();

  while (1) {
  }
  return 0;
}
