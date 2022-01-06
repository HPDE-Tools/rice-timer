#pragma once

#if TEST
#include "esp_task_wdt.h"
#include "unity.h"
extern "C" {
void unity_run_menu(void);
}
inline void RunTests() {
  esp_task_wdt_delete(xTaskGetIdleTaskHandle());
  unity_run_menu();
}
#else   // TEST
inline void RunTests() {}
#endif  // TEST
