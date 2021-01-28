#include <inttypes.h>
#include <sys/stat.h>
#include <chrono>
#include <memory>
#include <optional>
#include <string>

#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "driver/spi_common.h"
#include "fmt/chrono.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "sdmmc_cmd.h"
#include "soc/uart_struct.h"

#include "can.hpp"
#include "capture_manager.hpp"
#include "common.hpp"
#include "device/gps.hpp"
#include "filesystem.hpp"
#include "logger.hpp"
#include "ui/view.hpp"

namespace chrono = std::chrono;

namespace {

constexpr char TAG[] = "main";
constexpr int kI2cMaxFreqHz = 400'000;
constexpr int kGpsBaudRate = 38400;
constexpr int kGpsOutputPeriodMs = 200;

constexpr int kCanaryPeriodMs = 10000;

}  // namespace

esp_err_t SetupFileSystem() {
  if (/*CONFIG_SD_CARD_4BIT*/ false) {
    TRY(fs::InitializeSdCard());
  } else {
    TRY(fs::InitializeSdCardSpi());
  }
  sdmmc_card_print_info(stdout, fs::g_sd_card);
  TRY(mkdir(CONFIG_MOUNT_ROOT "/ghi", 0777) == 0 || errno == EEXIST ? ESP_OK : ESP_FAIL);
  TRY(mkdir(CONFIG_MOUNT_ROOT "/ghi/jkl", 0777) == 0 || errno == EEXIST ? ESP_OK : ESP_FAIL);
  {
    FILE* ftest;
    ftest = fopen(CONFIG_MOUNT_ROOT "/ghi/jkl/test.txt", "w");
    fputs("12345", ftest);
    fclose(ftest);
    ftest = fopen(CONFIG_MOUNT_ROOT "/ghi/jkl/test.txt", "r");
    static char buf[100] = {};
    fgets(buf, 100, ftest);
    ESP_LOGW(TAG, "read: %s", buf);
  }
  return ESP_OK;
}

std::unique_ptr<GpsManager> g_gps;

TaskHandle_t g_main_task{};
void MainTask(void* /* unused */) {
  vTaskDelay(pdMS_TO_TICKS(2000));  // let monitor connect

  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
  CHECK_OK(SetupFileSystem());

  g_gps = GpsManager::Create({
      .uart_num = UART_NUM_2,
      .uart_dev = &UART2,
      .uart_rx_pin = GPIO_NUM_16,
      .uart_tx_pin = GPIO_NUM_17,

      .pps_capture_unit = MCPWM_UNIT_0,
      .pps_capture_signal = MCPWM_SELECT_CAP0,
      .pps_capture_io = MCPWM_CAP_0,
      .pps_pin = GPIO_NUM_4,
      .software_capture_signal = MCPWM_SELECT_CAP2,

      .adjust_system_time = true,

      .priority = 3,
  });
  CHECK(g_gps);
  CHECK_OK(MtkDetectAndConfigure(g_gps.get(), kGpsBaudRate, kGpsOutputPeriodMs));

  CHECK_OK(LoggerInit());
  // CHECK_OK(PpsInit());
  // CHECK_OK(CanInit());
  // CHECK_OK(ui::ViewInit());

  CHECK_OK(LoggerStart());
  CHECK_OK(g_gps->Start());
  // CHECK_OK(PpsStart());
  // CHECK_OK(CanStart());
  // CHECK_OK(ui::ViewStart());

  vTaskDelete(nullptr);
}

#define LOG_WATER_MARK(name, task) \
  ESP_LOGI("canary", name ": %d", (task) ? uxTaskGetStackHighWaterMark((task)) : -1)

TaskHandle_t g_canary_task{};
void CanaryTask(void* /*unused*/) {
  TickType_t last_wake_tick = xTaskGetTickCount();
  while (true) {
    LOG_WATER_MARK("canary", g_canary_task);
    LOG_WATER_MARK("logger", g_logger_task);
    if (g_gps) {
      LOG_WATER_MARK("gps", g_gps->handle());
    }
    LOG_WATER_MARK("can", g_can_task);
    LOG_WATER_MARK("ui/view", ui::g_view_task);
    vTaskDelayUntil(&last_wake_tick, pdMS_TO_TICKS(kCanaryPeriodMs));
  }
}

extern "C" void app_main(void) {
  esp_log_level_set(TAG, ESP_LOG_INFO);
  esp_log_level_set("canary", ESP_LOG_INFO);

#if 0
  Serial.begin(kConsoleBaudHz);
  Wire.begin(23, 22, kI2cMaxFreqHz);
  Wire.begin(25, 26, kI2cMaxFreqHz);
#endif

  xTaskCreatePinnedToCore(
      CanaryTask,
      "canary",
      2500,
      /*arg*/ nullptr,
      configMAX_PRIORITIES - 2,
      &g_canary_task,
      PRO_CPU_NUM);
  xTaskCreatePinnedToCore(
      MainTask, "main", 4096, /*arg*/ nullptr, configMAX_PRIORITIES - 1, &g_main_task, APP_CPU_NUM);
}
