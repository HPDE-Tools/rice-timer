#include "can.hpp"

#include <charconv>
#include "fmt/core.h"
#include "fmt/format.h"

#include "driver/twai.h"
#include "esp_log.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "logger.hpp"

namespace {

constexpr char TAG[] = "can";

char* WriteHexUpper(char* s, uint32_t value, int len) {
  for (char* p = s + len - 1; p >= s; --p, value >>= 4) {
    *p = HexDigitUpper(value & 0xf);
  }
  return s + len - 1;
}

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
  return xTaskCreatePinnedToCore(CanTask, "can", 4096, nullptr, 4, &g_can_task, APP_CPU_NUM)
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
  // format: c,2147483647,b0b1b2b3,8,d0d1d2d3d4d5d6d7 (length 40)
  static char buf[41] = "c,";
  char* const buf_begin = buf + 2;
  char* const buf_end = buf + 41;

  while (true) {
    twai_message_t message;
    CHECK_OK(twai_receive(&message, portMAX_DELAY));
    const uint32_t current_capture =
        CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);

    // NOTE(summivox): manually format to (hopefully) save time
    char* p = buf_begin;
    p = std::to_chars(p, buf_end, current_capture, /*base*/ 10).ptr;
    *p++ = ',';
    p = WriteHexUpper(p, message.identifier, message.extd ? 8 : 3);
    *p++ = ',';
    *p++ = '0' + message.data_length_code;
    for (int i = 0; i < message.data_length_code; i++) {
      p = WriteHexUpper(p, message.data[i], 2);
    }
    *p++ = '\0';
    CHECK(p < buf_end);
    SendToLogger(std::string(buf, p));
#if 0
    {
      static TickType_t last_print = xTaskGetTickCount();
      if (xTaskGetTickCount() - last_print >= pdMS_TO_TICKS(100)) {
        last_print = xTaskGetTickCount();
        ESP_LOGW(TAG, "(%d)%s", p - buf, buf);
      }
    }
#endif
  }
}
