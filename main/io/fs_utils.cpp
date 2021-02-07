// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "io/fs_utils.hpp"

#include "unistd.h"

#include "driver/gpio.h"

#include "common/logging.hpp"

namespace io {

namespace {

constexpr char TAG[] = "fs";

}  // namespace

esp_err_t ReallyFlush(FILE* f) {
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

}  // namespace io
