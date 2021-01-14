#include "Arduino.h"

#include <optional>

#include "Adafruit_BNO055.h"
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "driver/mcpwm.h"
#include "freertos/FreeRTOS.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "gps.hpp"
#include "nameof.hpp"

constexpr char TAG[] = "main";
#define LED_BUILTIN 13

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_A, &Wire1);

char displaybuffer[4] = {' ', ' ', ' ', ' '};
void DisplayTask(void* /*unused*/) {
  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
    alpha4.writeDigitAscii(0, displaybuffer[0]);
    alpha4.writeDigitAscii(1, displaybuffer[1]);
    alpha4.writeDigitAscii(2, displaybuffer[2]);
    alpha4.writeDigitAscii(3, displaybuffer[3]);
    alpha4.writeDisplay();

    const int level = (millis() / 100) % 10 < 8;
    digitalWrite(LED_BUILTIN, level);

    // debug
    Serial.write("trig now: ");
    Serial.println(CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP1));

    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(250));
  }
}

void ImuTask(void* /*unused*/) {
  bno.setExtCrystalUse(true);

  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
    imu::Vector<3> v = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    Serial.printf("%.4f,%.4f,%.4f,", v[0], v[1], v[2]);
    imu::Quaternion q = bno.getQuat();
    Serial.printf("%.8f,%.8f,%.8f,%.8f,", q.w(), q.x(), q.y(), q.z());
    Serial.write('\n');
    vTaskDelayUntil(&last_wake_time, 10);
  }
}

TaskHandle_t g_gps_task;
esp_err_t GpsInit() {
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, GPIO_NUM_4));
  TRY(mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM_CAP_0, GPIO_NUM_4));
  return ESP_OK;
}

std::optional<uint32_t> g_capture_0{};
std::optional<uint32_t> g_capture_1{};
void IRAM_ATTR GpsPpsCapture(CaptureManager* manager,
                             mcpwm_capture_signal_t signal,
                             uint32_t edge,
                             uint32_t value) {

  if (manager->unit() == MCPWM_UNIT_0) {
    g_capture_0 = value;
  } else {
    g_capture_1 = value;
    value |= 1u << 31;
  }
  xTaskNotifyFromISR(g_gps_task, value, eSetValueWithOverwrite, nullptr);
}
void GpsTask(void* /*unused*/) {
  CaptureManager::GetInstance(MCPWM_UNIT_0)
      ->Subscribe(MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, /*prescaler*/ 0, GpsPpsCapture);
  CaptureManager::GetInstance(MCPWM_UNIT_1)
      ->Subscribe(MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, /*prescaler*/ 0, GpsPpsCapture);
  std::optional<uint32_t> last_capture{};
  while (true) {
    uint32_t curr_capture = 0;
    if (xTaskNotifyWait(0, 0, &curr_capture, pdMS_TO_TICKS(2000)) == pdFALSE) {
      Serial.printf("pps TIMEOUT");
      continue;
    }
    const uint32_t value = curr_capture & ~(1u << 31);
    const uint32_t unit = (curr_capture >> 31) & 1u;
    Serial.printf("pps capture%" PRIu32 " = %" PRIu32, unit, value);
    if (last_capture) {
      int32_t diff = value - *last_capture;
      Serial.printf(", diff = %" PRId32, diff);
    }
    if (g_capture_0 && g_capture_1) {
      int32_t diff01 = *g_capture_1 - *g_capture_0;
      Serial.printf(", diff01 = %" PRId32, diff01);
    } else {
      Serial.printf(", no diff01");
    }
    Serial.println();
    last_capture = value;
  }
}

extern "C" void app_main(void) {
  Serial.begin(115200);
  Wire.begin(23, 22);
  pinMode(LED_BUILTIN, OUTPUT);

  alpha4.begin(0x70);
#if 0
  if (!bno.begin()) {
    ESP_LOGE(TAG, "fail to init bno");
    while (true) {
    }
  }
#endif
  ESP_ERROR_CHECK(GpsInit());

  xTaskCreatePinnedToCore(DisplayTask, "display", 1024, nullptr, 2, nullptr, APP_CPU_NUM);
#if 0
  // xTaskCreatePinnedToCore(ImuTask, "imu", 1280, nullptr, 2, nullptr, APP_CPU_NUM);
#endif
  xTaskCreatePinnedToCore(GpsTask, "gps", 1280, nullptr, 2, &g_gps_task, APP_CPU_NUM);
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
}
