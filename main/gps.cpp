#include "gps.hpp"

#include "fmt/core.h"

#include "Arduino.h"
#include "driver/uart.h"
#include "esp_log.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "logger.hpp"

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

void ConfigureGps() {
  TakeArduinoMutex();
  SCOPE_EXIT { ReleaseArduinoMutex(); };

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
}

}  // namespace

TaskHandle_t g_gps_task;

esp_err_t GpsInit() {
  esp_log_level_set(TAG, ESP_LOG_INFO);
  ConfigureGps();
  return ESP_OK;
}

esp_err_t GpsStart() {
  return xTaskCreatePinnedToCore(GpsTask, "gps", 2560, nullptr, 1, &g_gps_task, APP_CPU_NUM)
             ? ESP_OK
             : ESP_FAIL;
}
void GpsStop() {
  if (g_gps_task) {
    vTaskDelete(g_gps_task);
    g_gps_task = nullptr;
  }
}

void GpsTask(void* /*unused*/) {
  static char buf[kGpsBufSize + 1] = {};
  while (true) {
    const int len = Serial1.readBytesUntil('\n', buf, kGpsBufSize);
    if (len > 0) {
      buf[len] = '\0';
      const uint32_t current_capture =
          CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);
      SendToLogger(fmt::format("g,{},{}", current_capture, buf));
    }
    {
      static int k = 0;
      if (++k == 10) {
        k = 0;
        ESP_LOGI(TAG, "water %d", uxTaskGetStackHighWaterMark(nullptr));
      }
    }
  }
}
