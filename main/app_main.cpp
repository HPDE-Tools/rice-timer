#include "Arduino.h"

#include "Adafruit_BNO055.h"
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "driver/mcpwm.h"

#include "gps.hpp"
#include "nameof.hpp"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif  // LED_BUILTIN

#define TRY(x)                                                     \
  do {                                                             \
    const esp_err_t xx = (x);                                      \
    if (xx != ESP_OK) {                                            \
      ESP_LOGE("", "TRY(" #x ") fail => %s", esp_err_to_name(xx)); \
      return xx;                                                   \
    }                                                              \
  } while (0)

constexpr char kLogTag[] = "main";

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

    vTaskDelayUntil(&last_wake_time, 10);
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

esp_err_t GpsInit() {
  mcpwm_unit_t unit = MCPWM_UNIT_0;
  TRY(mcpwm_gpio_init(unit, MCPWM_CAP_0, GPIO_NUM_4));
  TRY(mcpwm_capture_enable(unit, MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, 0));
  return ESP_OK;
}

void GpsTask(void* /*unused*/) {
  uint32_t last_capture = 0;
  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
    const uint32_t curr_capture = mcpwm_capture_signal_get_value(MCPWM_UNIT_0, MCPWM_SELECT_CAP0);
    Serial.printf("pps capture: %" PRIu32 ", diff = %" PRId32 "\n",
                  curr_capture,
                  static_cast<int32_t>(curr_capture - last_capture));
    last_capture = curr_capture;
    vTaskDelayUntil(&last_wake_time, 20);
  }
}

esp_err_t TryTestSub() {
  TRY(ESP_ERR_INVALID_MAC);
  return ESP_OK;
}

esp_err_t TryTest() {
  TRY(ESP_OK);
  TRY(TryTestSub());
  TRY(ESP_OK);
  return ESP_OK;
}

extern "C" void app_main(void) {
  Serial.begin(115200);
  Wire.begin(23, 22);
  Wire1.begin(27, 12);
  pinMode(LED_BUILTIN, OUTPUT);

  (void)TryTest();

  alpha4.begin(0x70);
  if (!bno.begin()) {
    ESP_LOGE(kLogTag, "fail to init bno");
    while (true) {
    }
  }
  ESP_ERROR_CHECK(GpsInit());

  xTaskCreatePinnedToCore(DisplayTask, "display", 1024, nullptr, 2, nullptr, APP_CPU_NUM);
  // xTaskCreatePinnedToCore(ImuTask, "imu", 1280, nullptr, 2, nullptr, APP_CPU_NUM);
  xTaskCreatePinnedToCore(GpsTask, "gps", 1280, nullptr, 2, nullptr, APP_CPU_NUM);
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
}
