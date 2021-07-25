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
#include "driver/twai.h"
#include "esp_freertos_hooks.h"
#include "fmt/chrono.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "minmea.h"
#include "sdmmc_cmd.h"

#include "app/can_instance.hpp"
#include "app/device_id.hpp"
#include "app/gps_instance.hpp"
#include "app/imu_instance.hpp"
#include "app/lap_timer.hpp"
#include "app/logger_instance.hpp"
#include "app/sd_card_instance.hpp"
#include "common/macros.hpp"
#include "common/strings.hpp"
#include "common/utils.hpp"
#include "ui/controller.hpp"
#include "ui/model.hpp"

namespace {
constexpr char TAG[] = "main";

constexpr int kCanaryPeriodMs = 991;
// constexpr int kCanaryPeriodMs = 9973;

}  // namespace

using namespace app;  // TODO: move this file altogether

void Main() {
  ESP_LOGI(TAG, "MainTask started");
  LogDeviceMac();
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
  // vTaskDelay(pdMS_TO_TICKS(2000));

  CHECK_OK(SetupSdCard());
  CHECK_OK(SetupLogger());
  CHECK_OK(SetupGps());
  CHECK_OK(SetupCan());
  CHECK_OK(SetupImu());
  // CHECK_OK(SetupLapTimer());
  CHECK_OK(ui::SetupUi());

  ESP_LOGI(TAG, "MainTask setup complete");
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);

  CHECK_OK(StartSdCardInstance());
  CHECK_OK(StartGpsInstance());
  CHECK_OK(StartCanInstance());
  CHECK_OK(StartImuInstance());
  // CHECK_OK(StartLapTimerTask());
  CHECK_OK(ui::StartUi());
}

TaskHandle_t g_main_task{};
void MainTask(void* /* unused */) {
  Main();
  vTaskDelete(nullptr);
}

#define LOG_WATER_MARK(name, task) \
  ESP_LOGI("canary", name ": %d", (task) ? uxTaskGetStackHighWaterMark((task)) : -1)

TaskHandle_t g_canary_task{};
void CanaryTask(void* /*unused*/) {
  TickType_t last_wake_tick = xTaskGetTickCount();
  while (true) {
    ESP_LOGW(
        "canary",
        "loss: g=%d i=%d c=%d",
        ui::g_model.lost.gps.load(),
        ui::g_model.lost.imu.load(),
        ui::g_model.lost.can.load());
#if 0
    LOG_WATER_MARK("canary", g_canary_task);
    if (g_logger) {
      LOG_WATER_MARK("logger", g_logger->handle());
    }
    if (g_gpsd) {
      LOG_WATER_MARK("gpsd", g_gpsd->handle());
    }
    if (g_can) {
      LOG_WATER_MARK("can", g_can->handle());
    }
    if (g_sd_card) {
      LOG_WATER_MARK("sd", g_sd_card->handle());
    }
    LOG_WATER_MARK("lap", GetLapTimerTask());
    if (ui::g_controller) {
      LOG_WATER_MARK("ui/view", ui::g_controller->handle());
    }
#endif
    vTaskDelayUntil(&last_wake_tick, pdMS_TO_TICKS(kCanaryPeriodMs));
  }
}

extern "C" void app_main(void) {
  CHECK_OK(NvsInit());

  // DEBUG: use SCL and SDA pin as debug
  gpio_set_direction(GPIO_NUM_17, GPIO_MODE_OUTPUT);
  gpio_pad_select_gpio(GPIO_NUM_17);
  gpio_set_direction(GPIO_NUM_16, GPIO_MODE_OUTPUT);
  gpio_pad_select_gpio(GPIO_NUM_16);

#if 0
  esp_register_freertos_idle_hook_for_cpu(
      []() {
        static bool level = false;
        gpio_set_level(GPIO_NUM_17, level ^= 1);
        return true;
      },
      PRO_CPU_NUM);
#endif

  xTaskCreatePinnedToCore(
      CanaryTask,
      "canary",
      2500,
      /*arg*/ nullptr,
      // configMAX_PRIORITIES - 2,
      0,
      &g_canary_task,
      PRO_CPU_NUM);
  xTaskCreatePinnedToCore(
      MainTask, "main", 4096, /*arg*/ nullptr, configMAX_PRIORITIES - 1, &g_main_task, APP_CPU_NUM);
}
