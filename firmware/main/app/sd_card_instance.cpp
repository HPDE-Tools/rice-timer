// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/sd_card_instance.hpp"

#include "sdmmc_cmd.h"

#include "app/logger_instance.hpp"
#include "common/iter.hpp"
#include "io/fs_utils.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "app/sd";

void HandleSdCardStateChange(bool mounted) {
  if (mounted) {
    sdmmc_card_print_info(stdout, g_sd_card->sd_card());
    ui::g_model.sd_card = ui::Model::SdCard{
        .capacity_bytes = g_sd_card->GetCapacityBytes(),
        .free_bytes = g_sd_card->GetFreeSpaceBytes(),
    };
    ESP_LOGI(TAG, "card mounted");
    // TODO: option for auto-start upon card mounted
#if 0
    const esp_err_t err = StartNewLoggingSession();
    if (err != ESP_OK) {
      ESP_LOGE(TAG, "logger cannot be started: %s", esp_err_to_name(err));
    }
#endif
    // DEBUG: test DirIter
    ESP_LOGE(TAG, "=== DirIter ===");
    for (auto x : RustIter<io::DirIter>(SD_FATFS_ROOT "/")) {
      ESP_LOGW(TAG, "%02x %s", x->fattrib, x->fname);
    }
  } else {
    ui::g_model.sd_card.reset();
    StopLogging();
    ESP_LOGW(TAG, "card unmounted");
  }
}

}  // namespace

std::unique_ptr<io::SdCardDaemon> g_sd_card;

esp_err_t SetupSdCard() {
  gpio_num_t card_detect_pin;
  if constexpr (CONFIG_HW_VERSION <= 2) {
    card_detect_pin = GPIO_NUM_27;
  } else if constexpr (CONFIG_HW_VERSION == 3) {
    card_detect_pin = GPIO_NUM_34;
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }

  g_sd_card = io::SdCardDaemon::Create(io::SdCardDaemon::Option{
      .mount_config =
          {
              .format_if_mount_failed = false,
              .max_files = 4,
              .allocation_unit_size = 0,  // only needed if format
          },
      .card_detect_pin = card_detect_pin,
      .priority = kPrioritySdCard,
  });
  return g_sd_card ? ESP_OK : ESP_FAIL;
}

esp_err_t StartSdCardInstance() {
  if (!g_sd_card) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_sd_card->Start(HandleSdCardStateChange);
}

}  // namespace app
