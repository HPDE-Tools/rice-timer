// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <cstdio>
#include <initializer_list>
#include <optional>
#include <string>
#include <string_view>

#include "driver/sdmmc_host.h"
#include "esp_err.h"
#include "ff.h"

#include "common/times.hpp"

namespace io {

// We won't be dealing with permissions
constexpr mode_t kFsMode = 0777;

// Fixed value for SDHC/SDXC
constexpr int kSdSectorSize = 512;

// Root directories (without trailing slashes)
#define SD_FATFS_ROOT "0:"
#define SD_VFS_ROOT CONFIG_MOUNT_ROOT
constexpr char kFatfsRoot[] = "0:";
constexpr char kVfsRoot[] = CONFIG_MOUNT_ROOT;

class DirIter {
 public:
  using Item = FILINFO*;
  DirIter() = default;
  DirIter(const char* path);
  ~DirIter();

  std::optional<FILINFO*> Next();

 private:
  std::optional<FF_DIR> dir_;
  FILINFO filinfo_;
};

esp_err_t FlushAndSync(FILE* f);

esp_err_t Mkdir(const std::string& dir);
esp_err_t MkdirParts(std::initializer_list<std::string_view> parts, std::string* out_path);

esp_err_t UpdateFileTime(const std::string& path, TimeUnix t_unix);

int32_t GetFreeSpaceSectors(const char* fatfs_root = kFatfsRoot);
int64_t GetFreeSpaceBytes(const char* fatfs_root = kFatfsRoot);

}  // namespace io
