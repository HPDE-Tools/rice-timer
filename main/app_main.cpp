#include <optional>

#include "Arduino.h"
#include "HardwareSerial.h"
#include "Wire.h"
#include "driver/spi_common.h"
#include "esp_vfs_fat.h"
#include "freertos/FreeRTOS.h"

#include "capture_manager.hpp"
#include "common.hpp"
#include "display.hpp"
#include "gps.hpp"
#include "imu.hpp"
#include "pps.hpp"

constexpr char TAG[] = "main";
constexpr int kConsoleBaudHz = 115200;
constexpr int kSdCardMaxFreqKhz = 40'000;
constexpr int kI2cMaxFreqHz = 400'000;

#define FS_ROOT "/sdcard"

sdmmc_card_t* g_sdcard{};
esp_err_t SetupFileSystem() {
  sdmmc_host_t host_config = SDSPI_HOST_DEFAULT();
  host_config.slot = HSPI_HOST;
  host_config.max_freq_khz = kSdCardMaxFreqKhz;

  sdspi_device_config_t io_config = SDSPI_DEVICE_CONFIG_DEFAULT();
  io_config.gpio_cs = GPIO_NUM_33;

  esp_vfs_fat_mount_config_t mount_config{
      .format_if_mount_failed = false,
      .max_files = 4,
      .allocation_unit_size = 5,
  };

  spi_bus_config_t bus_cfg = {
      .mosi_io_num = 18,
      .miso_io_num = 19,
      .sclk_io_num = 5,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 4000,
  };
  TRY(spi_bus_initialize(HSPI_HOST, &bus_cfg, HSPI_HOST));
  TRY(esp_vfs_fat_sdspi_mount(FS_ROOT, &host_config, &io_config, &mount_config, &g_sdcard));
  return ESP_OK;
}

TaskHandle_t g_main_task{};
void MainTask(void* /* unused */) {
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);

  SetupFileSystem();

  // CHECK_OK(DisplayInit());
  // CHECK_OK(DisplayStart());

  CHECK_OK(PpsInit());
  CHECK_OK(ImuInit());
  CHECK_OK(GpsInit());

  CHECK_OK(PpsStart());
  CHECK_OK(ImuStart());
  CHECK_OK(GpsStart());

  vTaskDelete(nullptr);
}

extern "C" void app_main(void) {
  esp_log_level_set(TAG, ESP_LOG_INFO);

  Serial.begin(kConsoleBaudHz);
  Wire.begin(23, 22, kI2cMaxFreqHz);
  InitI2cMutex();

  xTaskCreatePinnedToCore(
      MainTask, "main", 2048, /*arg*/ nullptr, configMAX_PRIORITIES - 1, &g_main_task, APP_CPU_NUM);
}
