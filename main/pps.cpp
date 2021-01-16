#include "pps.hpp"

#include <optional>
#include "fmt/core.h"

#include "driver/mcpwm.h"
#include "freertos/FreeRTOS.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "logger.hpp"
#include "ui/model.hpp"

constexpr char TAG[] = "pps";

TaskHandle_t g_pps_task;

namespace {

void IRAM_ATTR PpsCaptureCallback(CaptureManager* manager,
                                  mcpwm_capture_signal_t signal,
                                  uint32_t edge,
                                  uint32_t value) {
  xTaskNotifyFromISR(g_pps_task, value, eSetValueWithOverwrite, nullptr);
}

CaptureManager* g_capture_manager;

}  // namespace

std::optional<uint32_t> g_pps_latest_capture{};

esp_err_t PpsInit() {
  esp_log_level_set(TAG, ESP_LOG_INFO);
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, GPIO_NUM_4));
  TRY(mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM_CAP_0, GPIO_NUM_4));
  g_capture_manager = CaptureManager::GetInstance(MCPWM_UNIT_0);
  return ESP_OK;
}

esp_err_t PpsStart() {
  return xTaskCreatePinnedToCore(PpsTask, "pps", 2560, nullptr, 2, &g_pps_task, APP_CPU_NUM)
             ? ESP_OK
             : ESP_FAIL;
}

void PpsStop() {
  if (g_pps_task) {
    vTaskDelete(g_pps_task);
    g_pps_task = nullptr;
  }
}

void PpsTask(void* /*unused*/) {
  g_capture_manager->Subscribe(
      MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, /*prescaler*/ 0, PpsCaptureCallback);
  std::optional<uint32_t> last_capture{};
  while (true) {
    uint32_t current_capture = 0;
    if (xTaskNotifyWait(0, 0, &current_capture, pdMS_TO_TICKS(5000)) == pdFALSE) {
      ESP_LOGE(TAG, "PPS timeout");
      ui::g_model.pps_capture = std::nullopt;
      continue;
    }
    g_pps_latest_capture = current_capture;
    ui::g_model.pps_capture = current_capture;
    last_capture = current_capture;
    SendToLogger(fmt::format("p,{}", current_capture));
    ESP_LOGI(TAG, "water %d", uxTaskGetStackHighWaterMark(nullptr));
  }
}
