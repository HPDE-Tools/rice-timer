// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <algorithm>
#include <charconv>
#include <cinttypes>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "driver/gpio.h"
#include "esp_task_wdt.h"
#include "fmt/chrono.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"

#include "esp_freertos_hooks.h"  // depends on FreeRTOS.h

#include "app/analysis/onboard_analysis_instance.hpp"
#include "app/can_instance.hpp"
#include "app/device_id.hpp"
#include "app/gps_instance.hpp"
#include "app/imu_instance.hpp"
#include "app/logger_instance.hpp"
#include "app/sd_card_instance.hpp"
#include "common/macros.hpp"
#include "common/perf.hpp"
#include "common/strings.hpp"
#include "common/utils.hpp"
#include "run_tests.hpp"
#include "ui/controller.hpp"
#include "ui/model.hpp"

namespace {
constexpr char TAG[] = "main";

// constexpr int kCanaryPeriodMs = 991;
// constexpr int kCanaryPeriodMs = 9973;
constexpr int kCanaryPeriodMs = 5009;

}  // namespace

DECLARE_PERF(ui_controller);
DECLARE_PERF(onboard_analysis);

using fmt::print;

using namespace app;  // TODO: move this file altogether

void Main() {
  ESP_LOGI(TAG, "MainTask started");
  LogDeviceMac();
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
  // vTaskDelay(pdMS_TO_TICKS(2000));

  CHECK_OK(SetupSdCard());
  CHECK_OK(SetupAndStartLoggerTask());
  CHECK_OK(SetupGps());
  CHECK_OK(SetupCan());
  CHECK_OK(SetupImu());
  CHECK_OK(SetupOnboardAnalysis());
  CHECK_OK(ui::SetupUi());

  ESP_LOGI(TAG, "MainTask setup complete");
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);

  CHECK_OK(StartSdCardInstance());
  CHECK_OK(StartGpsInstance());
  CHECK_OK(StartCanInstance());
  CHECK_OK(StartImuInstance());
  CHECK_OK(StartOnboardAnalysisTask());
  CHECK_OK(ui::StartUi());
}

TaskHandle_t g_main_task{};
void MainTask(void* /* unused */) {
  RunTests();
  Main();
  vTaskDelete(nullptr);
}

#define LOG_WATER_MARK(name, task_handle) \
  ESP_LOGI("canary", name ": %d", (task_handle) ? uxTaskGetStackHighWaterMark((task_handle)) : -1)

#define LOG_WATER_MARK_P(name, task)            \
  do {                                          \
    if ((task)) {                               \
      LOG_WATER_MARK((name), (task)->handle()); \
    }                                           \
  } while (0)

TaskHandle_t g_canary_task{};
void CanaryTask(void* /*unused*/) {
  TickType_t last_wake_tick = xTaskGetTickCount();
  while (true) {
#if 0
    ESP_LOGW(
        "canary",
        "loss: g=%d i=%d c=%d",
        ui::g_model.lost.gps.load(),
        ui::g_model.lost.imu.load(),
        ui::g_model.lost.can.load());
#endif
    PERF_ui_controller.Dump();
    PERF_onboard_analysis.Dump();
#if 0
    LOG_WATER_MARK("canary", g_canary_task);
    LOG_WATER_MARK_P("logger", g_logger);
    LOG_WATER_MARK_P("gpsd", g_gpsd);
    LOG_WATER_MARK_P("can", g_can);
    LOG_WATER_MARK_P("sd", g_sd_card);
    LOG_WATER_MARK_P("lap", g_onboard_analysis);
    LOG_WATER_MARK_P("ui/view", ui::g_controller);
#endif
    vTaskDelayUntil(&last_wake_tick, pdMS_TO_TICKS(kCanaryPeriodMs));
  }
}

extern "C" void app_main(void) {
  CHECK_OK(NvsInit());

  // DEBUG: use SCL and SDA pin as debug
#if 0
  gpio_set_direction(GPIO_NUM_17, GPIO_MODE_OUTPUT);
  gpio_pad_select_gpio(GPIO_NUM_17);
  gpio_set_direction(GPIO_NUM_16, GPIO_MODE_OUTPUT);
  gpio_pad_select_gpio(GPIO_NUM_16);
#endif

#if 0
  esp_register_freertos_idle_hook_for_cpu(
      []() {
        static bool level = false;
        gpio_set_level(GPIO_NUM_17, level ^= 1);
        return true;
      },
      PRO_CPU_NUM);
#endif

#if !TEST
  xTaskCreatePinnedToCore(
      CanaryTask,
      "canary",
      4096,
      /*arg*/ nullptr,
      // configMAX_PRIORITIES - 2,
      0,
      &g_canary_task,
      PRO_CPU_NUM);
#endif

  xTaskCreatePinnedToCore(
      MainTask, "main", 8192, /*arg*/ nullptr, configMAX_PRIORITIES - 1, &g_main_task, APP_CPU_NUM);
}
