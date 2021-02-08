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
#include "freertos/ringbuf.h"  // NOTE: only in ESP32 port

#include "app/device_id.hpp"
#include "app/sd_card_instance.hpp"
#include "common/logging.hpp"
#include "common/scope_guard.hpp"
#include "common/strings.hpp"
#include "common/times.hpp"
#include "io/fs_utils.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

using app::g_sd_card;

namespace io {

namespace {
constexpr char TAG[] = "logger";
constexpr int kLoggerStackSize = 4096;
}  // namespace

Logger::Logger(std::string_view root_path, Option option)
    : root_(root_path),
      option_(option),
      ringbuf_(CHECK_NOTNULL(xRingbufferCreate(option.queue_size_bytes, RINGBUF_TYPE_NOSPLIT))) {}

Logger::~Logger() {
  Stop();
  vRingbufferDelete(ringbuf_);
}

esp_err_t Logger::Start(
    int64_t session_id,
    int split_id,
    Logger::CommitCallback commit_callback,
    Logger::StoppedCallback stopped_callback) {
  session_id_ = session_id;
  split_id_ = split_id % option_.split_overall_mod;
  commit_callback_ = commit_callback;
  stopped_callback_ = stopped_callback;
  DrainQueue();
  return Task::SpawnSame(TAG, kLoggerStackSize, kPriorityLogger);
}

void Logger::Stop(Error error) {
  if (stopped_callback_) {
    stopped_callback_(error);
  }
  Task::Kill();
}

esp_err_t Logger::AppendLine(std::string_view line, TickType_t timeout) {
  if (!Task::handle()) {
    return ESP_ERR_INVALID_STATE;
  }
  return xRingbufferSend(ringbuf_, line.data(), line.size(), timeout) == pdTRUE ? ESP_OK : ESP_FAIL;
}

esp_err_t Logger::AppendLineFromIsr(std::string_view line) {
  if (!Task::handle()) {
    return ESP_ERR_INVALID_STATE;
  }
  return xRingbufferSendFromISR(ringbuf_, line.data(), line.size(), nullptr) == pdTRUE ? ESP_OK :
                                                                                         ESP_FAIL;
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
    SCOPE_EXIT { fclose(file); };
    error = WriteIncomingLinesToFile(file);
    if (error != kNoError) {
      return;
    }
    if (++split_id_ == option_.split_overall_mod) {
      split_id_ = 0;
    }
  }
}

void Logger::DrainQueue() {
  // NOTE: this must be called BEFORE starting the task, so that there won't be new items pushed
  // into the queue (see `AppendLine`)
  size_t unused_size;
  void* item;
  while ((item = xRingbufferReceive(ringbuf_, &unused_size, 0)) != nullptr) {
    vRingbufferReturnItem(ringbuf_, item);
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
  lines_committed_ = 0;
  bytes_committed_ = 0;
  last_commit_time_ = xTaskGetTickCount();

  int64_t bytes_written = 0;
  for (int line = 0; line < option_.max_num_lines_per_split; ++line) {
    size_t size = 0;
    if (auto line =
            static_cast<char*>(xRingbufferReceive(ringbuf_, &size, option_.flush_interval_ms))) {
      SCOPE_EXIT { vRingbufferReturnItem(ringbuf_, line); };
      if (fwrite(line, size, 1, file) != 1 || fputc('\n', file) < 0) {
        ESP_LOGE(TAG, "fail to write (%s):%.*s", strerror(errno), size, line);
        return kWriteError;
      }
    }
    bytes_written += size;

    const TickType_t now = xTaskGetTickCount();
    if (SignedMinus(now, last_commit_time_) >= pdMS_TO_TICKS(option_.flush_interval_ms)) {
      if (const esp_err_t err = ReallyFlush(file); err != ESP_OK) {
        ESP_LOGE(TAG, "fail to flush (%s)", strerror(errno));
        return kFlushError;
      }
      lines_committed_ = line + 1;
      bytes_committed_ = bytes_written;
      last_commit_time_ = now;
      if (commit_callback_) {
        commit_callback_(*this, now);
      }
    }
  }
  return kNoError;
}

}  // namespace io
