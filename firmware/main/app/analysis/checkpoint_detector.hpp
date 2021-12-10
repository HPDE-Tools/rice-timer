// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "Eigen/Core"

#include "common/circular_buffer.hpp"
#include "interface/localization.hpp"
#include "map/map.hpp"
#include "math/segment2.hpp"
#include "math/utils.hpp"

namespace analysis {

class CheckpointDetector {
 public:
  static constexpr double kMaxDistanceToCenterM = 100.0;
  static constexpr double kMaxSqrDistanceToCenterM2 = math::Sqr(kMaxDistanceToCenterM);

  struct Result {
    int64_t timestamp_ms = 0;
    int checkpoint_index = 0;
  };

  CheckpointDetector();
  explicit CheckpointDetector(const map::Map* map);

  void SetMap(const map::Map* map);

  std::optional<Result> Detect(const CircularBuffer<MapLocalPose>& pose_history);

 private:
  const map::Map* map_ = nullptr;  // not owned

  int num_checkpoints_ = 0;
  std::vector<math::Segment2f> segments_;
  Eigen::Matrix2Xf centers_;
};

}  // namespace analysis
