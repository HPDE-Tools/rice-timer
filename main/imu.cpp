#include "imu.hpp"

#include "fmt/core.h"

#include "Arduino.h"
#include "Adafruit_BNO055.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "logger.hpp"

constexpr char TAG[] = "imu";

namespace {
Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_A);
}  // namespace

TaskHandle_t g_imu_task{};

esp_err_t ImuInit() {
  esp_log_level_set(TAG, ESP_LOG_INFO);

  TakeArduinoMutex();
  if (!bno.begin(Adafruit_BNO055::OPERATION_MODE_IMUPLUS)) {
    return ESP_ERR_NOT_FOUND;
  }
  bno.setExtCrystalUse(true);
  bno.setAxisRemap(Adafruit_BNO055::REMAP_CONFIG_P0);
  bno.setAxisSign(Adafruit_BNO055::REMAP_SIGN_P0);
  ReleaseArduinoMutex();

  // TODO(summivox): set up interrupt
  return ESP_OK;
}

esp_err_t ImuStart() {
  if (!xTaskCreatePinnedToCore(ImuTask, "imu", 4096, nullptr, 3, &g_imu_task, APP_CPU_NUM)) {
    return ESP_FAIL;
  }
  // TODO(summivox): set up interrupt
  return ESP_OK;
}

void ImuStop() {
  if (g_imu_task) {
    // TODO(summivox): set up interrupt
    vTaskDelete(g_imu_task);
    g_imu_task = nullptr;
  }
}

void ImuTask(void* /*unused*/) {
  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
    const uint32_t current_capture =
        CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);
    TakeArduinoMutex();
    const bool calibrated = bno.isFullyCalibrated();
    imu::Vector<3> a = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> w = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Quaternion q = bno.getQuat();
    ReleaseArduinoMutex();

    SendToLogger(fmt::format("i,{},{},{:.4},{:.4},{:.4},{:.4},{:.4},{:.4},{:.8},{:.8},{:.8},{:.8}",
                             current_capture,
                             int{calibrated},
                             a[0],
                             a[1],
                             a[2],
                             w[0],
                             w[1],
                             w[2],
                             q.w(),
                             q.x(),
                             q.y(),
                             q.z()));
    {
      static int k = 0;
      if (++k == 100) {
        k = 0;
        ESP_LOGI(TAG, "water %d", uxTaskGetStackHighWaterMark(nullptr));
      }
    }
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(10));
  }
}
