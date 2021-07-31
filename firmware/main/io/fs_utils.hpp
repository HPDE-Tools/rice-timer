// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <cstdio>
#include <initializer_list>
#include <optional>
#include <string>

#include "esp_err.h"

#include "common/times.hpp"
#include "driver/sdmmc_host.h"

namespace io {

// We won't be dealing with permissions
constexpr mode_t kFsMode = 0777;

// Fixed value for SDHC/SDXC
constexpr int kSdSectorSize = 512;

esp_err_t FlushAndSync(FILE* f);

esp_err_t Mkdir(const std::string& dir);
esp_err_t MkdirParts(std::initializer_list<std::string_view> parts, std::string* out_path);

esp_err_t UpdateFileTime(const std::string& path, TimeUnix t_unix);

int32_t GetFreeSpaceSectors(const char* fatfs_root = "0:");
int64_t GetFreeSpaceBytes(const char* fatfs_root = "0:");

}  // namespace io
