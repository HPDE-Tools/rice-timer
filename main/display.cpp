#include "display.hpp"

#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_SH110X.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include "common.hpp"

namespace {
Adafruit_SH110X display{64, 128, &Wire, -1, 400'000, 400'000};
}

constexpr char TAG[] = "display";
char g_display_content[9] = {};

#define LED_BUILTIN 13

TaskHandle_t g_display_task{};

esp_err_t DisplayInit() {
  TRY(gpio_set_direction(GPIO_NUM_13, GPIO_MODE_OUTPUT));
  // TODO(summivox): display

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
             DisplayTask, "display", 2048, nullptr, 3, &g_display_task, APP_CPU_NUM)
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
    digitalWrite(LED_BUILTIN, level);

#if 0
    TakeArduinoMutex();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(16, 24);
    display.write(g_display_content);
    display.display();
    ReleaseArduinoMutex();
#endif

    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(100));
  }
}
