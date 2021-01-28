#include "filesystem.hpp"

#include "unistd.h"

#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "esp_spi_flash.h"
#include "esp_vfs_fat.h"
#include "ff.h"
#include "sdmmc_cmd.h"

#include "common/logging.hpp"

namespace fs {

namespace {

constexpr char TAG[] = "fs";
constexpr int kSdSectorSize = 512;  // always 512 for SDHC and SDXC
constexpr int kSdClusterSize = 64 * kSdSectorSize;

}  // namespace

using std::nullopt;

sdmmc_card_t* g_sd_card{};

esp_err_t InitializeSdCard() {
  esp_vfs_fat_sdmmc_mount_config_t mount_config{
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = kSdClusterSize,
  };
  const char mount_point[] = MOUNT_POINT;
  ESP_LOGI(TAG, "Initializing SD card");

  ESP_LOGI(TAG, "Using SDMMC peripheral");
  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  host.max_freq_khz = SDMMC_FREQ_HIGHSPEED;

  // This initializes the slot without card detect (CD) and write protect (WP) signals.
  // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = 4;
  slot_config.gpio_cd = GPIO_NUM_27;

  // GPIOs 15, 2, 4, 12, 13 should have external 10k pull-ups.
  // Internal pull-ups are not sufficient. However, enabling internal pull-ups
  // does make a difference some boards, so we do that here.
  gpio_set_pull_mode(GPIO_NUM_15, GPIO_PULLUP_ONLY);  // CMD, needed in 4- and 1- line modes
  gpio_set_pull_mode(GPIO_NUM_2, GPIO_PULLUP_ONLY);   // D0, needed in 4- and 1-line modes
  gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);   // D1, needed in 4-line mode only
  gpio_set_pull_mode(GPIO_NUM_12, GPIO_PULLUP_ONLY);  // D2, needed in 4-line mode only
  gpio_set_pull_mode(GPIO_NUM_13, GPIO_PULLUP_ONLY);  // D3, needed in 4- and 1-line modes

  gpio_set_pull_mode(GPIO_NUM_27, GPIO_PULLUP_ONLY);  // detect

  TRY(esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &g_sd_card));
  sdmmc_card_print_info(stdout, g_sd_card);
  CHECK(g_sd_card->csd.sector_size == kSdSectorSize);
  return ESP_OK;
}

esp_err_t InitializeSdCardSpi() {
  sdmmc_host_t host_config = SDSPI_HOST_DEFAULT();
  host_config.slot = HSPI_HOST;
  host_config.max_freq_khz = 20'000;

  sdspi_device_config_t io_config = SDSPI_DEVICE_CONFIG_DEFAULT();
  io_config.gpio_cs = GPIO_NUM_33;

  esp_vfs_fat_mount_config_t mount_config{
      .format_if_mount_failed = false,
      .max_files = 4,
      .allocation_unit_size = CONFIG_WL_SECTOR_SIZE,
  };

  // TODO(summivox): flexible pinout
  spi_bus_config_t bus_cfg = {
      .mosi_io_num = 18,
      .miso_io_num = 19,
      .sclk_io_num = 5,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 0,
      .flags = 0,
      .intr_flags = 0,
  };
  TRY(spi_bus_initialize(HSPI_HOST, &bus_cfg, HSPI_HOST));
  TRY(esp_vfs_fat_sdspi_mount(
      CONFIG_MOUNT_ROOT, &host_config, &io_config, &mount_config, &fs::g_sd_card));
  return ESP_OK;
}

std::optional<int64_t> GetFreeSpaceBytes() {
  DWORD clust;
  FATFS* fatfs;
  FRESULT result = f_getfree("0:", &clust, &fatfs);
  if (result != FR_OK) {
    ESP_LOGE(TAG, "f_getfree => %d", result);
    return nullopt;
  }
  return int64_t{clust} * fatfs->csize * kSdSectorSize;
}

esp_err_t ReallyFlush(FILE* f) {
  if (f == nullptr) {
    return ESP_ERR_INVALID_ARG;
  }
  if (fflush(f) != 0) {
    return ESP_FAIL;
  }
  if (fsync(fileno(f)) != 0) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

}  // namespace fs
