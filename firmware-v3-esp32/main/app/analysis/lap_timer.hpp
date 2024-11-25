// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <limits>
#include <optional>
#include <vector>

namespace analysis {

class LapTimer {
 public:
  LapTimer();

  void Reset();

  void HitStartFinish(int64_t timestamp_ms);

  std::optional<int64_t> curr_lap_start_timestamp_ms() const {
    return curr_lap_start_timestamp_ms_;
  }
  const std::vector<int64_t>& start_finish_timestamps_ms() const {
    return start_finish_timestamps_ms_;
  }
  const std::vector<int64_t>& complete_lap_durations_ms() const {
    return complete_lap_durations_ms_;
  }
  int num_complete_laps() const { return complete_lap_durations_ms_.size(); }
  int64_t min_lap_duration_ms() const { return min_lap_duration_ms_; }
  int min_lap_index() const { return min_lap_index_; }

 private:
  std::optional<int64_t> curr_lap_start_timestamp_ms_{};
  std::vector<int64_t> start_finish_timestamps_ms_{};
  std::vector<int64_t> complete_lap_durations_ms_{};

  int64_t min_lap_duration_ms_ = std::numeric_limits<int64_t>::max();
  int min_lap_index_ = -1;
};

}  // namespace analysis
