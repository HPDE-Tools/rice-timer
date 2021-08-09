// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdio>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ringbuf_c/ringbuf.h"

#include "common/line_buffer_mpsc.hpp"
#include "common/macros.hpp"
#include "common/task.hpp"
#include "io/fs_utils.hpp"

namespace io {

class Logger : public Task {
 public:
  static constexpr char kLogFileSuffix[] = ".log";

  struct Option {
    /// Split file ID will roll over to 0 once it reaches this number.
    /// This is to prevent a single very long session producing astronomical split numbers that are
    /// rather hard to work with. The choice of this and `max_num_lines_per_split` should generally
    /// make sure that even this many empty lines will be too big for one SD card to hold.
    int split_overall_mod = 1'000'000;

    /// Use split file ID floor-divided by this as the containing dir name for the split file.
    /// This is to prevent (potentially) the session dir from housing too many files, which is
    /// considered pathological and can be difficult to handle by some tools.
    ///
    /// For example, if this is set to 1000, then the full path of split file "12345.txt" will be:
    /// "$session_dir/12/12345.txt"
    int split_prefix_div = 1'000;

    /// Each split file will contain at most this many lines.
    int max_num_lines_per_split = CONFIG_MAX_LINES_PER_FILE;

    /// Force flushing log to the card every once in a while.
    int flush_interval_ms = 1'013;

    /// Max number of bytes the incoming queue of the logger can hold.
    int queue_size_bytes = 8192;

    /// Target number of bytes written to the file in one `fwrite` call.
    int write_buffer_size_bytes = 512;

    /// If true, only keep the latest log on card when running out of space.
    /// If false, logging will stop without removing old log.
    bool rolling_log = true;

    /// If rolling log is enabled, start deleting from the oldest log files **within the same
    /// session**, until we have at least this much free space.
    int64_t rolling_headroom_bytes = 1 * 1024 * 1024;
  };

  enum State {
    kStopped,
    kRunning,
  };

  enum Error {
    kNoError,
    kInterrupted,
    kPathError,
    kHeadroomError,
    kOpenError,
    kWriteError,
    kFlushError,
  };

  using CommitCallback = std::function<void(const Logger& logger, TickType_t now)>;
  using StateChangeCallback = std::function<void(State state, Error last_error)>;

  Logger(
      std::string_view root_path,
      int num_producers,
      CommitCallback&& commit_callback,
      StateChangeCallback&& state_change_callback,
      Option option);
  virtual ~Logger();

  esp_err_t StartTask();

  esp_err_t StartNewSession();
  esp_err_t StopLogging();

  /// \param line content of the line (without line separator)
  IRAM_ATTR esp_err_t AppendLine(int producer_id, std::string_view line_without_sep);

  // split file path parts

  int64_t session_id() const { return session_id_; }
  int split_id() const { return split_id_; }
  const std::string& session_path() const { return session_path_; }
  const std::string& split_path() const { return split_path_; }

  // statistics

  int lines_committed() const { return lines_committed_; }
  int64_t bytes_committed() const { return bytes_committed_; }
  TickType_t last_commit_time() const { return last_commit_time_; }

 protected:
  void Run() override;

 private:
  enum Request : uint32_t {
    kRequestStop = 1,
    kRequestStart,
  };

  std::string root_;
  int num_producers_;
  CommitCallback commit_callback_ = nullptr;
  StateChangeCallback state_change_callback_ = nullptr;
  const Option option_;

  LineBufferMpsc line_buf_;
  std::vector<uint8_t> write_buf_;
  OwnedFile file_;

  State state_ = kStopped;
  Error last_error_ = kNoError;

  // session-split info

  int64_t session_id_ = 0;
  int split_id_ = 0;
  std::string session_path_{};
  std::string split_path_{};

  // split file info

  int lines_written_ = 0;
  int64_t bytes_written_ = 0;
  int lines_committed_ = 0;
  int64_t bytes_committed_ = 0;
  TickType_t last_commit_time_{};

  void ChangeState(State state);

  Error RunInternal();

  Error CheckInterruption();

  Error PrepareNewSession();
  Error PrepareNewSplit();
  Error EnsureSessionPath();
  Error EnsureSplitPath();
  Error MaintainRollingLogHeadroom();

  IRAM_ATTR Error WriteIncomingLines();
  IRAM_ATTR Error WriteIncomingLine(std::string_view line);
  Error FlushWriteBuf(bool sync);

  NON_COPYABLE_NOR_MOVABLE(Logger)
};

}  // namespace io
