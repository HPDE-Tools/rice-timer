#include "Arduino.h"

#include <algorithm>
#include <optional>

#include "Adafruit_BNO055.h"
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "driver/mcpwm.h"
#include "freertos/FreeRTOS.h"
#include "driver/uart.h"

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

    const int level = (millis() % 1000) < 200;
    digitalWrite(LED_BUILTIN, level);
  
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(100));
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

TaskHandle_t g_pps_task;
std::optional<uint32_t> g_pps_latest_capture{};
esp_err_t PpsInit() {
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, GPIO_NUM_4));
  TRY(mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM_CAP_0, GPIO_NUM_4));
  return ESP_OK;
}
void IRAM_ATTR GpsPpsCapture(CaptureManager* manager,
                             mcpwm_capture_signal_t signal,
                             uint32_t edge,
                             uint32_t value) {
  xTaskNotifyFromISR(g_pps_task, value, eSetValueWithOverwrite, nullptr);
}
void PpsTask(void* /*unused*/) {
  CaptureManager::GetInstance(MCPWM_UNIT_0)
      ->Subscribe(MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, /*prescaler*/ 0, GpsPpsCapture);
  std::optional<uint32_t> last_capture{};
  while (true) {
    uint32_t curr_capture = 0;
    if (xTaskNotifyWait(0, 0, &curr_capture, pdMS_TO_TICKS(5000)) == pdFALSE) {
      Serial.println("pps TIMEOUT");
      continue;
    }
    g_pps_latest_capture = curr_capture;

    Serial.printf("pps capture = %" PRIu32, curr_capture);
    if (last_capture) {
      int32_t diff = curr_capture - *last_capture;
      Serial.printf(", diff = %" PRId32, diff);
    }
    Serial.println();

    last_capture = curr_capture;
  }
}

constexpr uint32_t kGpsDetectTimeoutMs = 20000;
constexpr uint32_t kGpsDesiredBaudRate = 115200;
constexpr uint32_t kGpsDesiredBaudRateTolerance = 100;
constexpr uint32_t kGpsRetryMs = 2000;
constexpr size_t kGpsBufSize = 128;
TaskHandle_t g_gps_task;
void GpsTask(void* /*unused*/) {
  const uint32_t apb_freq = getApbFrequency();
  const float apb_period = 1.0 / apb_freq;
  ESP_LOGI(TAG, "capture clock: %d", apb_freq);
  // try detect presence and current baud rate
  while (true) {
    Serial1.end();
    ESP_LOGI(TAG, "GPS waiting for NMEA...");
    Serial1.begin(0, SERIAL_8N1, /*rx pin*/ 16, /*tx pin*/ 17, false, kGpsDetectTimeoutMs);
    if (!Serial1.availableForWrite()) {
      ESP_LOGW(TAG,
               "GPS NMEA not detected for %" PRIu32 " ms; retry in %" PRIu32 " ms",
               kGpsDetectTimeoutMs,
               kGpsRetryMs);
      vTaskDelay(pdMS_TO_TICKS(kGpsRetryMs));
      continue;
    }
    const uint32_t current_baud = Serial1.baudRate();
    ESP_LOGI(TAG, "GPS NMEA detected; baud = %" PRIu32, current_baud);
    if (!(kGpsDesiredBaudRate - kGpsDesiredBaudRateTolerance <= current_baud &&
          current_baud <= kGpsDesiredBaudRate + kGpsDesiredBaudRateTolerance)) {
      ESP_LOGI(TAG, "GPS attempt to change baud to %" PRIu32, kGpsDesiredBaudRate);
      Serial1.write("$PMTK251,115200*1F\r\n");
      vTaskDelay(pdMS_TO_TICKS(kGpsRetryMs));
      continue;
    }
    break;
  }
  // configure output rate and type

  // Serial1.write("$PMTK220,200*2C\r\n");  // 5 Hz
  Serial1.write("$PMTK220,100*2F\r\n");  // 10 Hz
  Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");  // GPRMC
  // Serial1.write("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n");  // GPRMC,GPGGA

  static char buf[kGpsBufSize] = {};
  while (true) {
    const int len = Serial1.readBytesUntil('\n', buf, kGpsBufSize);
    const uint32_t current_capture = CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);
    if (len > 0) {
      Serial.print(current_capture);
      if (g_pps_latest_capture) {
        const int32_t diff = current_capture - *g_pps_latest_capture;
        const float diff_sec = diff * apb_period;
        Serial.printf("(%+.3f)", diff_sec);
      }
      Serial.write(':');
      Serial.write(buf, len);
      Serial.write('\n');
    }
    vTaskDelay(1);
  }
}

extern "C" void app_main(void) {
  Serial.begin(115200);
  Wire.begin(23, 22);
  pinMode(LED_BUILTIN, OUTPUT);
  esp_log_level_set(TAG, ESP_LOG_INFO);

  alpha4.begin(0x70);
#if 0
  if (!bno.begin()) {
    ESP_LOGE(TAG, "fail to init bno");
    while (true) {
    }
  }
#endif
  ESP_ERROR_CHECK(PpsInit());

  xTaskCreatePinnedToCore(DisplayTask, "display", 1280, nullptr, 2, nullptr, APP_CPU_NUM);
#if 0
  // xTaskCreatePinnedToCore(ImuTask, "imu", 1280, nullptr, 2, nullptr, APP_CPU_NUM);
#endif
  xTaskCreatePinnedToCore(PpsTask, "pps", 1280, nullptr, 2, &g_pps_task, APP_CPU_NUM);
  xTaskCreatePinnedToCore(GpsTask, "gps", 2560, nullptr, 1, &g_gps_task, APP_CPU_NUM);
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
}
