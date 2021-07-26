// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "io/logger.hpp"

#include <inttypes.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <cstdio>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "esp_log.h"
#include "esp_system.h"
#include "fmt/core.h"
#include "ringbuf_c/ringbuf.h"
#include "scope_guard/scope_guard.hpp"

#include "app/device_id.hpp"
#include "app/sd_card_instance.hpp"
#include "common/macros.hpp"
#include "common/strings.hpp"
#include "common/times.hpp"
#include "io/fs_utils.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

// TODO(summivox): Decouple from SD card instance
using app::g_sd_card;

namespace io {

namespace {
constexpr char TAG[] = "logger";
constexpr int kLoggerStackSize = 4096;
}  // namespace

#define LOGGER_TRY(expr)                                     \
  do {                                                       \
    if (const Logger::Error err = (expr); err != kNoError) { \
      return err;                                            \
    }                                                        \
  } while (0)

Logger::Logger(std::string_view root_path, int num_producers, Option option)
    : root_(root_path), option_(option), line_buf_(option.queue_size_bytes, num_producers) {
  write_buf_.reserve(option.write_buffer_size_bytes);
}

Logger::~Logger() { Stop(); }

esp_err_t Logger::Start(
    Logger::CommitCallback commit_callback, Logger::StoppedCallback stopped_callback) {
  session_id_ = app::NewSessionId();
  split_id_ = 0;
  commit_callback_ = commit_callback;
  stopped_callback_ = stopped_callback;
  line_buf_.Clear();
  return Task::SpawnPinned(TAG, kLoggerStackSize, kPriorityLogger, PRO_CPU_NUM);
}

void Logger::Stop(Error error) {
  if (stopped_callback_) {
    stopped_callback_(error);
  }
  Task::Kill();
}

esp_err_t Logger::AppendLine(int producer_id, std::string_view line_without_sep) {
  if (!Task::handle()) {
    return ESP_ERR_INVALID_STATE;
  }
  return line_buf_.Push(producer_id, line_without_sep) ? ESP_OK : ESP_FAIL;
}

void Logger::Run() {
  // NOTE: SCOPE_EXIT will take care of clean up in case of early termination (`return` below)
  Error error = kNoError;
  SCOPE_EXIT {
    // if we bailed, probably it's because the card got unplugged, so check that first
    g_sd_card->Ping();
    Stop(error);
  };

  if (!EnsureSessionDir()) {
    error = kPathError;
    return;
  }
  while (true) {
    if (!EnsureSplitPath()) {
      error = kPathError;
      return;
    }
    if (option_.rolling_log) {
      if (!MaintainRollingLogHeadroom()) {
        error = kHeadroomError;
        return;
      }
    }
    ESP_LOGI(TAG, "will open file: %s", split_path_.c_str());
    FILE* file = fopen(split_path_.c_str(), "w");
    if (file == nullptr) {
      error = kOpenError;
      return;
    }
    SCOPE_EXIT {
      ESP_LOGW(TAG, "will close file: %s", split_path_.c_str());
      fclose(file);
    };
    error = WriteIncomingLinesToFile(file);
    if (error != kNoError) {
      return;
    }
    if (++split_id_ == option_.split_overall_mod) {
      split_id_ = 0;
    }
  }
}

bool Logger::EnsureSessionDir() {
  if (const esp_err_t err = MkdirParts({root_, std::to_string(session_id_)}, &session_dir_);
      err != ESP_OK) {
    ESP_LOGE(TAG, "error making session dir:%s (%s)", session_dir_.c_str(), strerror(errno));
    return false;
  }
  return true;
}

bool Logger::EnsureSplitPath() {
  const int split_prefix = split_id_ / option_.split_prefix_div;
  const std::string split_prefix_str = std::to_string(split_prefix);
  const std::string split_id_str = std::to_string(split_id_);

  // Full path: $session/$prefix/$split.log
  // By now "$session" have already been created, so we only need to work on the rest.
  split_path_.clear();
  split_path_.reserve(
      session_dir_.size() + 1 + split_prefix_str.size() + 1 + split_id_str.size() +
      sizeof(kLogFileSuffix));
  split_path_ += session_dir_;
  split_path_ += '/';
  split_path_ += split_prefix_str;

  if (const esp_err_t err = Mkdir(split_path_); err != ESP_OK) {
    ESP_LOGE(TAG, "error making split dir:%s (%s)", split_path_.c_str(), strerror(errno));
    split_path_.clear();
    return false;
  }

  split_path_ += '/';
  split_path_ += split_id_str;
  split_path_ += kLogFileSuffix;
  return true;
}

bool Logger::MaintainRollingLogHeadroom() {
  const int64_t headroom_bytes = option_.rolling_headroom_bytes;
  while (true) {
    const int64_t free_space_bytes = g_sd_card->GetFreeSpaceBytes();
    if (free_space_bytes < 0) {
      ESP_LOGE(TAG, "cannot get free space");
      return false;
    }
    if (free_space_bytes >= headroom_bytes) {
      return true;
    }
    // TODO(summivox):
    // - list and sort index of existing log files under `root_`
    // - delete until satisfactory
    CHECK(false && "rolling log is unimplemented");
  }
  return true;
}

Logger::Error Logger::WriteIncomingLinesToFile(FILE* file) {
  /////////////// DEBUG
  // gpio_set_level(GPIO_NUM_17, 0);
  // gpio_set_level(GPIO_NUM_16, 0);

  lines_written_ = 0;
  bytes_written_ = 0;
  lines_committed_ = 0;
  bytes_committed_ = 0;
  last_commit_time_ = xTaskGetTickCount();

  std::string_view line;
  for (int line_i = 0; line_i < option_.max_num_lines_per_split; line_i++) {
    while (true) {
      line = line_buf_.Peek();
      if (line.empty()) {
        vTaskDelay(1);
        continue;
      }
      break;
    }
    LOGGER_TRY(WriteIncomingLineToFile(line, file));
    line_buf_.PopPeeked(line);
  }
  return FlushWriteBuf(file, /*sync*/ true);
}

Logger::Error Logger::WriteIncomingLineToFile(std::string_view line, FILE* file) {
  const TickType_t now = xTaskGetTickCount();
  const bool buf_full = (write_buf_.size() + line.size() > write_buf_.capacity());
  const bool should_sync =
      (SignedMinus(now, last_commit_time_) >= pdMS_TO_TICKS(option_.flush_interval_ms));
  if (buf_full || should_sync) {
    LOGGER_TRY(FlushWriteBuf(file, should_sync));
  }
  CHECK(write_buf_.size() + line.size() <= write_buf_.capacity());
  write_buf_.insert(write_buf_.end(), line.begin(), line.end());
  lines_written_++;
  bytes_written_ += line.size();
  return kNoError;
}

Logger::Error Logger::FlushWriteBuf(FILE* file, bool sync) {
  if (!write_buf_.empty()) {
    // gpio_set_level(GPIO_NUM_17, 1);  // DEBUG
    if (fwrite(write_buf_.data(), write_buf_.size(), 1, file) != 1) {
      ESP_LOGE(
          TAG, "fail to write (%s):%.*s", strerror(errno), write_buf_.size(), write_buf_.data());
      return kWriteError;
    }
    write_buf_.clear();
    // gpio_set_level(GPIO_NUM_17, 0);  // DEBUG
  }

  if (sync) {
    // gpio_set_level(GPIO_NUM_16, 1);  // DEBUG
    if (const esp_err_t err = FlushAndSync(file); err != ESP_OK) {
      ESP_LOGE(TAG, "fail to flush (%s)", strerror(errno));
      return kFlushError;
    }
    lines_committed_ = lines_written_;
    bytes_committed_ = bytes_written_;
    last_commit_time_ = xTaskGetTickCount();
    if (commit_callback_) {
      commit_callback_(*this, last_commit_time_);
    }
    // gpio_set_level(GPIO_NUM_16, 0);  // DEBUG
  }

  return kNoError;
}

}  // namespace io
