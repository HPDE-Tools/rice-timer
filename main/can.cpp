#include "can.hpp"

#include "fmt/core.h"
#include "fmt/format.h"

#include "driver/twai.h"
#include "esp_log.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "logger.hpp"

namespace {

constexpr char TAG[] = "can";

}  // namespace

TaskHandle_t g_can_task{};

esp_err_t CanInit() {
  esp_log_level_set(TAG, ESP_LOG_INFO);
  twai_general_config_t general_config =
      TWAI_GENERAL_CONFIG_DEFAULT(/*tx*/ GPIO_NUM_12, /*rx*/ GPIO_NUM_27, TWAI_MODE_NORMAL);
  general_config.intr_flags = ESP_INTR_FLAG_IRAM;
  general_config.tx_queue_len = 0;
  twai_timing_config_t timing_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t filter_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  return twai_driver_install(&general_config, &timing_config, &filter_config);
}

esp_err_t CanStart() {
  TRY(twai_start());
  return xTaskCreatePinnedToCore(CanTask, "can", 2560, nullptr, 4, &g_can_task, APP_CPU_NUM)
             ? ESP_OK
             : ESP_FAIL;
}

void CanStop() {
  CHECK_OK(twai_stop());
  if (g_can_task) {
    vTaskDelete(g_can_task);
    g_can_task = nullptr;
  }
}

void CanTask(void* /*unused*/) {
  static fmt::basic_memory_buffer<char, 50, std::allocator<char>> buf;
  while (true) {
    twai_message_t message;
    CHECK_OK(twai_receive(&message, portMAX_DELAY));
    const uint32_t current_capture =
        CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);
    buf.clear();
    if (message.extd) {
      fmt::format_to(
          buf, "c,{},{:08X},{},", current_capture, message.identifier, message.data_length_code);
    } else {
      fmt::format_to(
          buf, "c,{},{:03X},{},", current_capture, message.identifier, message.data_length_code);
    }
    for (int i = 0; i < message.data_length_code; i++) {
      fmt::format_to(buf, "{:02X}", message.data[i]);
    }
    buf.push_back('\0');
    SendToLogger(std::string(buf.data()));
  }
}
