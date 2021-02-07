// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/sd_card_instance.hpp"

#include "priorities.hpp"

namespace app {

std::unique_ptr<io::SdCardDaemon> g_sd_card;

esp_err_t SetupSdCard() {
  g_sd_card = io::SdCardDaemon::Create({
      .mount_config =
          {
              .format_if_mount_failed = false,
              .max_files = 4,
              .allocation_unit_size = 0,  // only needed if format
          },
      .card_detect_pin = GPIO_NUM_27,
      .priority = kPrioritySdCard,
  });
  return g_sd_card ? ESP_OK : ESP_FAIL;
}

}  // namespace app
