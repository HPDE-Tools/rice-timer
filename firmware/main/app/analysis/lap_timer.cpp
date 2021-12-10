// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/analysis/lap_timer.hpp"

#include <cstdint>
#include <optional>

#include "common/circular_buffer.hpp"
#include "interface/localization.hpp"
#include "map/map.hpp"
#include "math/segment2.hpp"
#include "math/utils.hpp"

namespace analysis {

LapTimer::LapTimer() {}

void LapTimer::Reset() {
  curr_lap_start_timestamp_ms_.reset();
  start_finish_timestamps_ms_.clear();
  complete_lap_durations_ms_.clear();
  min_lap_duration_ms_ = std::numeric_limits<int64_t>::max();
  min_lap_index_ = -1;
}

void LapTimer::HitStartFinish(int64_t timestamp_ms) {
  start_finish_timestamps_ms_.push_back(timestamp_ms);
  if (curr_lap_start_timestamp_ms_) {
    const int64_t duration = timestamp_ms - *curr_lap_start_timestamp_ms_;
    complete_lap_durations_ms_.push_back(duration);
    if (duration < min_lap_duration_ms_) {
      min_lap_duration_ms_ = duration;
      min_lap_index_ = complete_lap_durations_ms_.size() - 1;
    }
  }
  curr_lap_start_timestamp_ms_ = timestamp_ms;
}

}  // namespace analysis
