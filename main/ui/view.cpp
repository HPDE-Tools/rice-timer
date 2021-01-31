#include "ui/view.hpp"

#include <optional>

#include "driver/gpio.h"
#include "esp_log.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
// #include "lvgl.h"

#include "common/logging.hpp"
#include "ui/model.hpp"

namespace ui {
namespace {}  // namespace

constexpr char TAG[] = "ui/view";

TaskHandle_t g_view_task{};

esp_err_t ViewInit() {
  // TODO
  return ESP_OK;
}

esp_err_t ViewStart() {
  return xTaskCreatePinnedToCore(ViewTask, "ui/view", 4096, nullptr, 20, &g_view_task, APP_CPU_NUM)
             ? ESP_OK
             : ESP_FAIL;
}

void ViewStop() {
  if (g_view_task) {
    vTaskDelete(g_view_task);
    g_view_task = nullptr;
  }
}

void ViewTask(void* /*unused*/) {
  int x0 = 1;
  int y0 = 0;
  ESP_LOGW(TAG, "random base: x = %d, y = %d", x0, y0);
  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
#if 0
    TakeArduinoMutex();
    display.clearDisplay();

    display.setTextColor(SH110X_WHITE);

    display.setTextSize(1);  // w6 x h8
    display.setFont(nullptr);
    if (g_model.gps) {
      const auto& g = *g_model.gps;
      display.setCursor(x0 + 0, y0 + 0);
      display.write(fmt::format("{:+9.5f} {:+10.5f}", g.latitude, g.longitude).c_str());
    }

    display.setFont(&FreeSans18pt7b);
    display.setTextSize(1);
    if (g_model.gps) {
      const auto& g = *g_model.gps;
      display.setCursor(0, y0 + 37);
      display.write(fmt::format("{:02}", g.hour).c_str());
      display.setCursor(43 * 1, y0 + 37);
      display.write(fmt::format("{:02}", g.minute).c_str());
      display.setCursor(43 * 2, y0 + 37);
      display.write(fmt::format("{:02}", g.second).c_str());
      display.writeFastHLine(x0 + g.millisecond / 100 * 11, y0 + 42, 11, SH110X_WHITE);
    }

    display.setFont(nullptr);
    display.setTextSize(1);
    if (g_model.imu) {
      const auto& imu = *g_model.imu;
      display.setCursor(x0 + 0, y0 + 44);

      // NOTE(summivox): for now, use ghetto axis conversion after-the-fact; also use g as unit
      constexpr float gg = 1 / 9.79;
      display.write(
          fmt::format("{:+6.3f} {:+6.3f} {:+6.3f}", -imu.ay * gg, imu.ax * gg, imu.az * gg)
              .c_str());
    }

    display.setFont(nullptr);
    display.setTextSize(1);
    display.setCursor(x0 + 0, y0 + 54);
    display.write(fmt::format("{}/{}", g_model.logger_session_id, g_model.logger_split_id).c_str());

    display.drawRect(62, y0 + 55, 64, 5, SH110X_WHITE);
    display.fillRect(
        62, y0 + 55, g_model.logger_lines * 64 / CONFIG_MAX_LINES_PER_FILE, 5, SH110X_WHITE);

    display.display();
    ReleaseArduinoMutex();
#endif

    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(100));
  }
}

}  // namespace ui
