// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "io/sd_card_daemon.hpp"

#include <optional>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "scope_guard/scope_guard.hpp"

#include "common/isr_yielder.hpp"
#include "common/macros.hpp"

namespace io {

namespace {
constexpr char TAG[] = "sd";
constexpr char kFatFsRoot[] = "0:";

constexpr int kSdStackDepth = 4096;

}  // namespace

SdCardDaemon::SdCardDaemon(Option option) : option_(option) {}

esp_err_t SdCardDaemon::Setup() {
  // All pins below are fixed. All pins require 10k pull up except for CLK.
  //
  // | ESP32 pin     | SD card pin | SPI pin |
  // |---------------|-------------|---------|
  // | GPIO14 (MTMS) | CLK         | SCK     |
  // | GPIO15 (MTDO) | CMD         | MOSI    |
  // | GPIO2         | D0          | MISO    |
  // | GPIO4         | D1          | N/C     |
  // | GPIO12 (MTDI) | D2          | N/C     |
  // | GPIO13 (MTCK) | D3          | CS      |
  //

  gpio_set_pull_mode(GPIO_NUM_15, GPIO_PULLUP_ONLY);  // CMD, needed in 4- and 1- line modes
  gpio_set_pull_mode(GPIO_NUM_2, GPIO_PULLUP_ONLY);   // D0, needed in 4- and 1-line modes
  gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);   // D1, needed in 4-line mode only
  gpio_set_pull_mode(GPIO_NUM_12, GPIO_PULLUP_ONLY);  // D2, needed in 4-line mode only
  gpio_set_pull_mode(GPIO_NUM_13, GPIO_PULLUP_ONLY);  // D3, needed in 4- and 1-line modes

  gpio_config_t card_detect_pin_config{
      .pin_bit_mask = (uint64_t{1} << option_.card_detect_pin),
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_ANYEDGE,
  };
  gpio_pad_select_gpio(option_.card_detect_pin);
  gpio_config(&card_detect_pin_config);

  // okay if GPIO ISR is already installed
  if (const esp_err_t err = gpio_install_isr_service(ESP_INTR_FLAG_IRAM);
      err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
    return err;
  }

  TRY(gpio_isr_handler_add(option_.card_detect_pin, (void (*)(void*))HandleCardDetectEvent, this));
  return ESP_OK;
}

void SdCardDaemon::Teardown() {
  Stop();
  UnmountInternal();
}

esp_err_t SdCardDaemon::Start(MountStateChangeCallback callback) {
  callback_ = callback;
  TRY(Task::SpawnSame(TAG, kSdStackDepth, option_.priority));
  gpio_intr_enable(option_.card_detect_pin);
  return ESP_OK;
}

void SdCardDaemon::Stop() {
  gpio_intr_disable(option_.card_detect_pin);
  Task::Kill();
  callback_ = nullptr;
}

void SdCardDaemon::Ping() {
  if (const TaskHandle_t handle = Task::handle()) {
    xTaskNotify(handle, 1, eSetBits);
  }
}

void SdCardDaemon::PingFromIsr() {
  if (const TaskHandle_t handle = Task::handle()) {
    IsrYielder yielder;
    xTaskNotifyFromISR(handle, 1, eSetBits, yielder);
  }
}

void SdCardDaemon::HandleCardDetectEvent(SdCardDaemon* self) { self->PingFromIsr(); }

void SdCardDaemon::Run() {
  while (true) {
    const bool card_inserted = GetCardDetected();
    if (DoTheRightThing(card_inserted)) {
      xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);
    } else {
      const int retry_ms = option_.mount_retry_time_ms;
      vTaskDelay(pdMS_TO_TICKS(retry_ms + esp_random() % (retry_ms / 2)));
    }
  }
}

bool SdCardDaemon::DoTheRightThing(bool card_inserted) {
  if (!card_inserted) {
    ESP_LOGV(TAG, "card=out --- unmount");
    UnmountInternal();
    return true;
  }

  if (sd_card_) {
    if (CheckIsCardWorking()) {
      ESP_LOGV(TAG, "card=in, mounted=yes, valid=yes --- nop");
    } else {
      ESP_LOGV(TAG, "card=in, mounted=yes, valid=no --- unmount then retry with delay");
      UnmountInternal();
      return false;
    }
  } else {
    ESP_LOGV(TAG, "card=in, mounted=no --- mount");
    if (const esp_err_t err = MountInternal(); err != ESP_OK) {
      ESP_LOGV(TAG, "failed to mount --- retry with delay");
      return false;
    }
  }

  return true;
}

esp_err_t SdCardDaemon::MountInternal() {
  CHECK(sd_card_ == nullptr);
  sdmmc_host_t host = SDMMC_HOST_DEFAULT();
  host.max_freq_khz = SDMMC_FREQ_HIGHSPEED;

  sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
  slot_config.width = 4;
  // slot_config.gpio_cd = option_.card_detect_pin;  // we will handle the pin ourselves

  TRY(esp_vfs_fat_sdmmc_mount(
      CONFIG_MOUNT_ROOT, &host, &slot_config, &option_.mount_config, &sd_card_));

  if (callback_) {
    callback_(true);
  }
  return ESP_OK;
}

bool SdCardDaemon::UnmountInternal() {
  if (sd_card_) {
    // NOTE(summivox): Unfortunately this call is not thread-safe, and might fail when another
    // thread is halfway through a VFS operation. I haven't found a way to avoid this, partially
    // because there's no library function to "close everything" before/upon unmount.
    esp_vfs_fat_sdcard_unmount(CONFIG_MOUNT_ROOT, sd_card_);
    sd_card_ = nullptr;
    if (callback_) {
      callback_(false);
    }
    return true;
  }
  return false;
}

bool SdCardDaemon::CheckIsCardWorking() { return GetFreeSpaceSectors() >= 0; }

int32_t SdCardDaemon::GetFreeSpaceSectors() {
  if (!sd_card_) {
    return -1;
  }
  DWORD clust;
  FATFS* fatfs;
  FRESULT result = f_getfree(kFatFsRoot, &clust, &fatfs);
  if (result != FR_OK) {
    ESP_LOGE(TAG, "f_getfree => %d", result);
    return -1;
  }
  // free space sectors <= card capacity sectors, which is stored as int32_t
  return static_cast<int32_t>(clust) * fatfs->csize;
}

int64_t SdCardDaemon::GetFreeSpaceBytes() {
  // NOTE(summivox): reason this is not implemented thru GetFreeSpaceSectors: we need `fatfs` too.
  if (!sd_card_) {
    return -1;
  }
  DWORD clust;
  FATFS* fatfs;
  FRESULT result = f_getfree(kFatFsRoot, &clust, &fatfs);
  if (result != FR_OK) {
    ESP_LOGE(TAG, "f_getfree => %d", result);
    return -1;
  }
  return int64_t{clust} * fatfs->csize * kSdSectorSize;
}

int32_t SdCardDaemon::GetCapacitySectors() {
  if (!sd_card_) {
    return -1;
  }
  return sd_card_->csd.capacity;
}

int64_t SdCardDaemon::GetCapacityBytes() {
  if (!sd_card_) {
    return -1;
  }
  return int64_t{sd_card_->csd.capacity} * kSdSectorSize;
}

}  // namespace io
