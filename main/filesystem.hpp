// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <cstdio>
#include <optional>

#include "esp_err.h"

#include "driver/sdmmc_host.h"

namespace fs {

extern sdmmc_card_t* g_sd_card;

esp_err_t InitializeSdCard();
esp_err_t InitializeSdCardSpi();
std::optional<int64_t> GetFreeSpaceBytes();
esp_err_t ReallyFlush(FILE* f);

}  // namespace fs
