// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "io/logger.hpp"

#include <inttypes.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "esp_log.h"
#include "esp_system.h"
#include "ringbuf_c/ringbuf.h"
#include "scope_guard/scope_guard.hpp"

#include "app/device_id.hpp"
#include "common/macros.hpp"
#include "common/strings.hpp"
#include "common/times.hpp"
#include "io/fs_utils.hpp"
#include "priorities.hpp"

namespace io {

namespace {
constexpr char TAG[] = "logger";
constexpr int kLoggerStackSize = 4096;
}  // namespace

/// `TRY` macro for control flow within Logger
#define LOGGER_TRY(expr)                                                         \
  do {                                                                           \
    if (const Logger::Error err = (expr); err != kNoError) {                     \
      ESP_LOGW(TAG, "%s:%d TRY(%s) fail => %d", __FILE__, __LINE__, #expr, err); \
      return err;                                                                \
    }                                                                            \
  } while (0)

/// shorthand for marking "interruptable" points in the logger workflow
#define LOGGER_YIELD LOGGER_TRY(CheckInterruption())

Logger::Logger(
    std::string_view root_path,
    int num_producers,
    Logger::CommitCallback&& commit_callback,
    Logger::StateChangeCallback&& state_change_callback,
    Option option)
    : root_(root_path),
      commit_callback_(commit_callback),
      state_change_callback_(state_change_callback),
      option_(option),
      line_buf_(option.queue_size_bytes, num_producers),
      file_(nullptr, fclose) {}

Logger::~Logger() { Task::Kill(); }

esp_err_t Logger::StartTask() {
  return Task::SpawnPinned(TAG, kLoggerStackSize, kPriorityLogger, PRO_CPU_NUM);
}

esp_err_t Logger::StartNewSession() {
  if (!Task::handle()) {
    return ESP_ERR_INVALID_STATE;
  }
  xTaskNotify(Task::handle(), kRequestStart, eSetValueWithOverwrite);
  return ESP_OK;
}

esp_err_t Logger::StopLogging() {
  if (!Task::handle()) {
    return ESP_ERR_INVALID_STATE;
  }
  xTaskNotify(Task::handle(), kRequestStop, eSetValueWithOverwrite);
  return ESP_OK;
}

esp_err_t Logger::AppendLine(int producer_id, std::string_view line_without_sep) {
  if (!(Task::handle() && state_ == kRunning)) {
    return ESP_ERR_INVALID_STATE;
  }
  total_lines_in_++;
  return line_buf_.Push(producer_id, line_without_sep) ? ESP_OK : ESP_FAIL;
}

void Logger::Run() {
  while (true) {
    ESP_LOGI(TAG, "awaiting request...");
    uint32_t request{};
    xTaskNotifyWait(/*clear entry*/ 0, /*clear exit*/ ~0u, &request, portMAX_DELAY);
    ESP_LOGI(TAG, "got request: %d", (int)request);
    switch (request) {
      case kRequestStart: {
        last_error_ = kNoError;
        ChangeState(kRunning);
      } break;
      case kRequestStop:
        if (state_ == kRunning) {
          file_.reset();
          ChangeState(kStopped);
          line_buf_.Clear();  // NOTE: must be done after changing state
        }
        break;
      default:
        break;
    }
    if (state_ == kRunning) {
      last_error_ = RunInternal();
      if (!(last_error_ == kNoError || last_error_ == kInterrupted)) {
        ChangeState(kStopped);
      }
    }
  }
}

void Logger::ChangeState(State state) {
  state_ = state;
  if (state_change_callback_) {
    state_change_callback_(state, last_error_);
  }
}

Logger::Error Logger::RunInternal() {
  LOGGER_TRY(PrepareNewSession());
  while (true) {
    if (option_.rolling_log) {
      LOGGER_TRY(MaintainRollingLogHeadroom());
    }
    LOGGER_TRY(PrepareNewSplit());
    LOGGER_TRY(WriteIncomingLines());
  }
}

Logger::Error Logger::CheckInterruption() {
  uint32_t request{};
  if (xTaskNotifyWait(/*clear entry*/ 0, /*clear exit*/ 0, &request, /*timeout*/ 0) == pdTRUE &&
      request) {
    // hack: re-send the value so that the main loop can process it later
    xTaskNotify(Task::handle(), request, eSetValueWithOverwrite);
    return kInterrupted;
  }
  return kNoError;
}

Logger::Error Logger::PrepareNewSession() {
  LOGGER_YIELD;
  session_id_ = app::NewSessionId();
  if (session_id_ < 0) {
    return kPathError;
  }
  split_id_ = -1;
  LOGGER_TRY(EnsureSessionPath());
  return kNoError;
}

Logger::Error Logger::PrepareNewSplit() {
  LOGGER_YIELD;
  if (++split_id_ == option_.split_overall_mod) {
    split_id_ = 0;
  }
  LOGGER_TRY(EnsureSplitPath());
  ESP_LOGI(TAG, "will open file: %s", split_path_.c_str());
  FILE* file = fopen(split_path_.c_str(), "w");
  if (!file) {
    return kOpenError;
  }
  file_.reset(file);
  if (auto err = setvbuf(file, NULL, _IOFBF, option_.write_buffer_size_bytes); err != 0) {
    ESP_LOGE(TAG, "setvbuf to %d bytes => fail %d", option_.write_buffer_size_bytes, err);
    return kOpenError;
  }
  return kNoError;
}

Logger::Error Logger::EnsureSessionPath() {
  if (const esp_err_t err = MkdirParts({root_, std::to_string(session_id_)}, &session_path_);
      err != ESP_OK) {
    ESP_LOGE(TAG, "error making session dir:%s (%s)", session_path_.c_str(), strerror(errno));
    return kPathError;
  }
  return kNoError;
}

Logger::Error Logger::EnsureSplitPath() {
  const int split_prefix = split_id_ / option_.split_prefix_div;
  const std::string split_prefix_str = std::to_string(split_prefix);
  const std::string split_id_str = std::to_string(split_id_);

  // Full path: $session/$prefix/$split.log
  // By now "$session" have already been created, so we only need to work on the rest.
  split_path_.clear();
  split_path_.reserve(
      session_path_.size() + 1 + split_prefix_str.size() + 1 + split_id_str.size() +
      sizeof(kLogFileSuffix));
  split_path_ += session_path_;
  split_path_ += '/';
  split_path_ += split_prefix_str;

  if (const esp_err_t err = Mkdir(split_path_); err != ESP_OK) {
    ESP_LOGE(TAG, "error making split dir:%s (%s)", split_path_.c_str(), strerror(errno));
    split_path_.clear();
    return kPathError;
  }

  split_path_ += '/';
  split_path_ += split_id_str;
  split_path_ += kLogFileSuffix;
  return kNoError;
}

Logger::Error Logger::MaintainRollingLogHeadroom() {
  const int64_t headroom_bytes = option_.rolling_headroom_bytes;
  while (true) {
    const int64_t free_space_bytes = io::GetFreeSpaceBytes();
    if (free_space_bytes < 0) {
      ESP_LOGE(TAG, "cannot get free space");
      return kHeadroomError;
    }
    if (free_space_bytes >= headroom_bytes) {
      return kNoError;
    }
    // TODO(summivox):
    // - list and sort index of existing log files under `root_`
    // - delete until satisfactory
    CHECK(false && "rolling log is unimplemented");
  }
  return kNoError;
}

Logger::Error Logger::WriteIncomingLines() {
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
      LOGGER_YIELD;
      line = line_buf_.Peek();
      if (line.empty()) {
        vTaskDelay(1);
        continue;
      }
      break;
    }
    LOGGER_TRY(WriteIncomingLine(line));
    line_buf_.PopPeeked(line);
  }
  return Flush();
}

Logger::Error Logger::WriteIncomingLine(std::string_view line) {
  const TickType_t now = xTaskGetTickCount();
  const bool should_sync =
      (SignedMinus(now, last_commit_time_) >= pdMS_TO_TICKS(option_.flush_interval_ms));

  if (fwrite(line.data(), line.size(), 1, file_.get()) != 1) {
    ESP_LOGE(TAG, "fail to write (%s):%.*s", strerror(errno), line.size(), line.data());
    return kWriteError;
  }

  lines_written_++;
  bytes_written_ += line.size();
  total_lines_out_++;

  if (should_sync) {
    return Flush();
  }
  return kNoError;
}

Logger::Error Logger::Flush() {
  // gpio_set_level(GPIO_NUM_16, 1);  // DEBUG
  if (const esp_err_t err = FlushAndSync(file_.get()); err != ESP_OK) {
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
  return kNoError;
}

}  // namespace io
