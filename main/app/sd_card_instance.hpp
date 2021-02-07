// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"

#include "io/sd_card_daemon.hpp"

namespace app {

extern std::unique_ptr<io::SdCardDaemon> g_sd_card;

esp_err_t SetupSdCard();

}  // namespace app
