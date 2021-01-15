#include "imu.hpp"

#include "Arduino.h"

#include "Adafruit_BNO055.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#include "common.hpp"

constexpr char TAG[] = "imu";

namespace {
Adafruit_BNO055 bno = Adafruit_BNO055(BNO055_ID, BNO055_ADDRESS_A);
}  // namespace

TaskHandle_t g_imu_task{};

esp_err_t ImuInit() {
  TakeI2cMutex();
  if (!bno.begin(Adafruit_BNO055::OPERATION_MODE_IMUPLUS)) {
    return ESP_ERR_NOT_FOUND;
  }
  bno.setExtCrystalUse(true);
  ReleaseI2cMutex();
  // TODO(summivox): set up interrupt
  return ESP_OK;
}

esp_err_t ImuStart() {
  if (!xTaskCreatePinnedToCore(ImuTask, "imu", 2560, nullptr, 2, &g_imu_task, APP_CPU_NUM)) {
    return ESP_FAIL;
  }
  // TODO(summivox): set up interrupt
  return ESP_OK;
}

void ImuStop() {
  if (g_imu_task) {
    // TODO(summivox): set up interrupt
    vTaskDelete(g_imu_task);
  }
}

void ImuTask(void* /*unused*/) {
  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
    imu::Vector<3> a = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    imu::Vector<3> w = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    imu::Quaternion q = bno.getQuat();
#if 0
    Serial.printf("%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.8f,%.8f,%.8f,%.8f\n",
                  a[0],
                  a[1],
                  a[2],
                  w[0],
                  w[1],
                  w[2],
                  q.w(),
                  q.x(),
                  q.y(),
                  q.z());
#endif
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(50));
  }
}
