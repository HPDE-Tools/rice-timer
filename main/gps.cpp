#include "gps.hpp"

#include "Arduino.h"
#include "driver/uart.h"
#include "esp_log.h"

#include "capture_manager.hpp"
#include "common.hpp"

constexpr char TAG[] = "gps";

constexpr uint32_t kGpsDetectTimeoutMs = 20000;
constexpr uint32_t kGpsDesiredBaudRate = 115200;
constexpr uint32_t kGpsDesiredBaudRateTolerance = 100;
constexpr uint32_t kGpsRetryMs = 2000;
constexpr size_t kGpsBufSize = 128;

namespace {

bool TryDetectGps(uint32_t timeout_tick) {
  Serial1.end();
  Serial1.begin(0, SERIAL_8N1, /*rx pin*/ 16, /*tx pin*/ 17, false, kGpsDetectTimeoutMs);
  return Serial1.availableForWrite();
}

void ConfigureBaud() {
  // TODO(summivox): make this configurable (necessary?!)
  Serial1.write("$PMTK251,115200*1F\r\n");
}

}  // namespace

TaskHandle_t g_gps_task;

esp_err_t GpsInit() {
  // NOP --- we will autobaud later
  return ESP_OK;
}

esp_err_t GpsStart() {
  return xTaskCreatePinnedToCore(GpsTask, "gps", 2560, nullptr, 1, &g_gps_task, APP_CPU_NUM)
             ? ESP_OK
             : ESP_FAIL;
}

void GpsTask(void* /*unused*/) {
  // try detect presence and current baud rate
  while (true) {
    ESP_LOGI(TAG, "GPS waiting for NMEA...");
    if (!TryDetectGps(kGpsDetectTimeoutMs)) {
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
      ConfigureBaud();
      vTaskDelay(pdMS_TO_TICKS(kGpsRetryMs));
      continue;
    }
    break;
  }
  // configure output rate and type

  // Serial1.write("$PMTK220,200*2C\r\n");  // 5 Hz
  Serial1.write("$PMTK220,100*2F\r\n");                                    // 10 Hz
  Serial1.write("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");  // GPRMC
  // Serial1.write("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n");  // GPRMC,GPGGA

  static char buf[kGpsBufSize] = {};
  while (true) {
    const int len = Serial1.readBytesUntil('\n', buf, kGpsBufSize);
    const uint32_t current_capture =
        CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);
    if (len > 0) {
      Serial.print(current_capture);

#if 0  // TODO(summivox): GPS-PPS link will be pushed upwards thru e.g. callback
      if (g_pps_latest_capture) {
        const int32_t diff = current_capture - *g_pps_latest_capture;
        const float diff_sec = diff * apb_period;
        Serial.printf("(%+.3f)", diff_sec);
      }
#endif

      Serial.write(':');
      Serial.write(buf, len);
      Serial.write('\n');
    }
    vPortYield();
  }
}
