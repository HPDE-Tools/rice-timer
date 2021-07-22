// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/sd_card_instance.hpp"

#include "sdmmc_cmd.h"

#include "app/logger_instance.hpp"
#include "priorities.hpp"

namespace app {

namespace {

constexpr char TAG[] = "app/sd";

void HandleSdCardStateChange(bool mounted) {
  if (mounted) {
    sdmmc_card_print_info(stdout, g_sd_card->sd_card());
    ESP_LOGI(TAG, "card mounted; starting logger");
    const esp_err_t err = StartLogger();
    if (err != ESP_OK) {
      ESP_LOGE(TAG, "logger cannot be started: %s", esp_err_to_name(err));
    }
  } else {
    StopLogger();
    ESP_LOGW(TAG, "card unmounted; logger stopped");
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
