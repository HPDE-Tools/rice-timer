// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <algorithm>
#include <charconv>
#include <cinttypes>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "argtable3/argtable3.h"
#include "driver/gpio.h"
#include "esp_task_wdt.h"
#include "freertos/FreeRTOS.h"
#include "linenoise/linenoise.h"

#include "esp_freertos_hooks.h"  // depends on FreeRTOS.h

#include "app/analysis/onboard_analysis_instance.hpp"
#include "app/can_instance.hpp"
#include "app/device_id.hpp"
#include "app/gps_instance.hpp"
#include "app/heartbeat.hpp"
#include "app/imu_instance.hpp"
#include "app/logger_instance.hpp"
#include "app/sd_card_instance.hpp"
#include "common/console_command.hpp"
#include "common/console_command_registry.hpp"
#include "common/macros.hpp"
#include "common/perf.hpp"
#include "common/strings.hpp"
#include "common/utils.hpp"
#include "priorities.hpp"
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

using namespace app;  // TODO: move this file altogether

esp_console_repl_t* InitializeConsole() {
  esp_console_repl_t* repl = nullptr;
  esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
  repl_config.task_priority = kPriorityBackground;
  repl_config.prompt = "rice>";
  esp_console_dev_uart_config_t repl_uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
  OK_OR_RETURN(esp_console_new_repl_uart(&repl_uart_config, &repl_config, &repl), nullptr);
  OK_OR_RETURN(ConsoleCommandRegistry::GetInstance()->Register(), nullptr);
  linenoiseSetMultiLine(0);
  return repl;
}

DEFINE_CONSOLE_COMMAND(lsheap, "print heap details", nullptr, {}, 1) {
  printf("\n");
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
  printf("\n");
  return 0;
}

void Main() {
  ESP_LOGI(TAG, "MainTask started");
  LogDeviceMac();
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
  // vTaskDelay(pdMS_TO_TICKS(2000));

  esp_console_repl_t* repl = InitializeConsole();

  CHECK_OK(SetupSdCard());
  CHECK_OK(SetupAndStartLoggerTask());
  CHECK_OK(SetupHeartbeat());
  CHECK_OK(SetupGps());
  CHECK_OK(SetupCan());
  CHECK_OK(SetupImu());
  CHECK_OK(SetupOnboardAnalysis());
  CHECK_OK(ui::SetupUi());

  ESP_LOGI(TAG, "MainTask setup complete");
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);

  CHECK_OK(StartSdCardInstance());
  CHECK_OK(StartHeartbeat());
  CHECK_OK(StartGpsInstance());
  CHECK_OK(StartCanInstance());
  CHECK_OK(StartImuInstance());
  CHECK_OK(StartOnboardAnalysisTask());
  CHECK_OK(ui::StartUi());

  if (repl) {
    esp_console_start_repl(repl);
  }
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
#if 0
    PERF_ui_controller.Dump();
    PERF_onboard_analysis.Dump();
#endif
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
