#include "display.hpp"

#include <optional>

#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_SH110X.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#include "common.hpp"
#include "pps.hpp"

// TODO(summivox): invert dependency and introduce MV(C?)
// for now we will simply show PPS capture result

namespace {
Adafruit_SH110X display{64, 128, &Wire, -1, 400'000, 400'000};
}

constexpr char TAG[] = "display";
char g_display_content[9] = {};

#define LED_BUILTIN GPIO_NUM_13

TaskHandle_t g_display_task{};

esp_err_t DisplayInit() {
  gpio_pad_select_gpio(LED_BUILTIN);
  TRY(gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT));

  TakeArduinoMutex();
  display.begin();
  display.clearDisplay();
  display.display();
  display.setRotation(1);
  ReleaseArduinoMutex();

  return ESP_OK;
}

esp_err_t DisplayStart() {
  return xTaskCreatePinnedToCore(
             DisplayTask, "display", 3000, nullptr, 20, &g_display_task, APP_CPU_NUM)
             ? ESP_OK
             : ESP_FAIL;
}

void DisplayStop() {
  if (g_display_task) {
    vTaskDelete(g_display_task);
    g_display_task = nullptr;
  }
}

void DisplayTask(void* /*unused*/) {
  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
    const int level = (millis() % 1000) < 200;
    gpio_set_level(LED_BUILTIN, level);

    if (g_pps_latest_capture) {
      TakeArduinoMutex();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(16, 24);
      display.printf("%08X", *g_pps_latest_capture);
      display.display();
      ReleaseArduinoMutex();
    }

    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(100));
  }
}
