// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <optional>

#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "esp_vfs_fat.h"

#include "common/task.hpp"

#ifndef CONFIG_MOUNT_ROOT
#define CONFIG_MOUNT_ROOT "/s"
#endif  // CONFIG_MOUNT_ROOT

namespace io {

// TODO(summivox): add support for no detect pin (just poll)

class SdCardDaemon : public Task {
 public:
  static constexpr int kSdSectorSize = 512;  // fixed number for SDHC/SDXC

  struct Option {
    esp_vfs_fat_sdmmc_mount_config_t mount_config;

    gpio_num_t card_detect_pin = GPIO_NUM_NC;
    int mount_retry_time_ms = 1000;

    int priority = 0;
  };
  using MountStateChangeCallback = std::function<void(bool mounted)>;

  static std::unique_ptr<SdCardDaemon> Create(Option option) {
    std::unique_ptr<SdCardDaemon> self{new SdCardDaemon(option)};
    if (self->Setup() != ESP_OK) {
      self.reset();
    }
    return self;
  }
  virtual ~SdCardDaemon() { Teardown(); }

  esp_err_t Start(MountStateChangeCallback callback);
  void Stop();

  /// Prompts the daemon to take a look at the current state of the card and take appropriate
  /// action. Should be called from task context.
  void Ping();

  /// Prompts the daemon to take a look at the current state of the card and take appropriate
  /// action. Should be called from ISR context.
  void IRAM_ATTR PingFromIsr();

  /// Validate if the SD card is actually operational
  bool CheckIsCardWorking();

  /// Reads how many sectors (= 512 Bytes for SDHC/SDXC) are free on the card.
  ///
  /// \return -1 if no card or error
  ///         number of sectors (>= 0) free otherwise
  int32_t GetFreeSpaceSectors();

  /// Reads how many bytes are free on the card.
  ///
  /// \return -1 if no card or error
  ///         number of bytes (>= 0) free otherwise
  int64_t GetFreeSpaceBytes();

  /// Reads the capacity of the card in sectors (= 512 Bytes for SDHC/SDXC)
  ///
  /// \return -1 if no card or error
  ///         number of sectors (>= 0) total otherwise
  int32_t GetCapacitySectors();

  /// Reads the capacity of the card in bytes
  ///
  /// \return -1 if no card or error
  ///         number of sectors (>= 0) total otherwise
  int64_t GetCapacityBytes();

  /// Read the card detection pin to check the presence of a SD card
  ///
  /// \return true if the card appears to be inserted;
  ///         false otherwise
  bool GetCardDetected() const { return !gpio_get_level(option_.card_detect_pin); }

  sdmmc_card_t* sd_card() const { return sd_card_; }

 protected:
  void Run() override;

 private:
  Option option_;
  sdmmc_card_t* sd_card_ = nullptr;
  MountStateChangeCallback callback_;

  explicit SdCardDaemon(Option option);

  esp_err_t Setup();
  void Teardown();

  /// Mounts the SD card VFS.
  /// Assumes the card is currently unmounted (will check).
  esp_err_t MountInternal();

  /// Unmounts the SD card VFS if not already unmounted.
  ///
  /// \return true if the card was mounted => now unmounted
  ///         false if the card was unmounted (no-op)
  bool UnmountInternal();

  /// For a lack of better words, take the appropriate action to maintain card mounting state in
  /// sync with card insertion state.
  ///
  /// \param card_inserted
  /// \return true if the action (or inaction) is successful
  ///         false if exception happened and we need to retry
  bool DoTheRightThing(bool card_inserted);

  static void IRAM_ATTR HandleCardDetectEvent(SdCardDaemon* self);
};

}  // namespace io
