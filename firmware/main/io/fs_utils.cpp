// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "io/fs_utils.hpp"

extern "C" {
#include <sys/stat.h>
#include <sys/unistd.h>
#include <utime.h>
}

#include <algorithm>
#include <cstdio>
#include <initializer_list>
#include <numeric>

#include "driver/gpio.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

#include "common/macros.hpp"
#include "common/times.hpp"

namespace io {

namespace {

constexpr char TAG[] = "fs";

}  // namespace

esp_err_t FlushAndSync(FILE* f) {
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

OwnedFile OpenFile(const std::string& path, const char* modestr) {
  return OwnedFile(fopen(path.c_str(), modestr), fclose);
}

esp_err_t ReadBinaryFileToString(const std::string& path, std::string* out_file_content) {
  ESP_LOGI(TAG, "ReadBinaryFileToString(%s)", path.c_str());
  OwnedFile f = OpenFile(path, "rb");
  if (!f) {
    ESP_LOGE(TAG, "ReadBinaryFileToString(%s) => %s", path.c_str(), strerror(errno));
    return ESP_ERR_NOT_FOUND;
  }
  FILE* const ff = f.get();
  if (fseek(ff, 0, SEEK_END) != 0) {
    return ESP_FAIL;
  }
  auto len = ftell(ff);
  if (len < 0) {
    return ESP_FAIL;
  }
  if (fseek(ff, 0, SEEK_SET) != 0) {
    return ESP_FAIL;
  }
  ESP_LOGI(TAG, "file len: %d", static_cast<int>(len));
  out_file_content->resize(static_cast<size_t>(len));
  if (len > 0) {
    if (fread(out_file_content->data(), len, 1, ff) != 1) {
      return ESP_FAIL;
    }
  }
  return ESP_OK;
}

esp_err_t Mkdir(const std::string& dir) {
  // this is infrequent enough we can afford logging every call
  ESP_LOGI(TAG, "Mkdir: %s", dir.c_str());
  const int result = mkdir(dir.c_str(), kFsMode);
  return (result == 0 || errno == EEXIST) ? ESP_OK : ESP_FAIL;
}

esp_err_t MkdirParts(std::initializer_list<std::string_view> parts, std::string* out_path) {
  // basically `join(parts, '/')`
  CHECK(out_path != nullptr);
  int len = parts.size();
  for (const auto& part : parts) {
    len += part.size();
  }
  out_path->clear();
  out_path->reserve(len);
  for (const auto& part : parts) {
    (*out_path) += part;
    TRY(Mkdir(*out_path));
    (*out_path) += '/';
  }
  CHECK(out_path->size() == len);
  out_path->resize(len - 1);  // trim the trailing slash
  return ESP_OK;
}

esp_err_t UpdateFileTime(const std::string& path, TimeUnix t_unix) {
  // TODO(summivox): consider validity of current system time
  utimbuf buf{.actime = t_unix, .modtime = t_unix};
  if (esp_vfs_utime(path.c_str(), &buf) != 0) {
    ESP_LOGE(TAG, "utimes(%s, %d) fail => %s", path.c_str(), (int)t_unix, strerror(errno));
    return ESP_FAIL;
  }
  return ESP_OK;
}

int32_t GetFreeSpaceSectors(const char* fatfs_root) {
  DWORD clust;
  FATFS* fatfs;
  FRESULT result = f_getfree(fatfs_root, &clust, &fatfs);
  if (result != FR_OK) {
    ESP_LOGE(TAG, "f_getfree => %d", result);
    return -1;
  }
  // free space sectors <= card capacity sectors, which is stored as int32_t
  return static_cast<int32_t>(clust) * fatfs->csize;
}

int64_t GetFreeSpaceBytes(const char* fatfs_root) {
  // NOTE(summivox): reason this is not implemented thru GetFreeSpaceSectors: we need `fatfs` too.
  DWORD clust;
  FATFS* fatfs;
  FRESULT result = f_getfree(fatfs_root, &clust, &fatfs);
  if (result != FR_OK) {
    ESP_LOGE(TAG, "f_getfree => %d", result);
    return -1;
  }
  return int64_t{clust} * fatfs->csize * kSdSectorSize;
}

}  // namespace io
