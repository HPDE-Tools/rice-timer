// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <vector>

#include "Eigen/Core"

namespace map {
class Map;
}  // namespace map

struct CheckpointHit {
  int checkpoint_index;
  float speed;
  float course_rad;
};

struct LapTraceSample {
  float s;      // station (of the S-L coordinate system) [m]
  float l;      // lateral offset (of the S-L coordinate system) [m]
  float speed;  // scalar speed [m/s]
};

struct MapBoundLapTrace {
  struct Segment {
    int track_index;
    std::vector<LapTraceSample> samples;
    // time since the beginning of the trace for each sample [ms]
    std::vector<int32_t> t_ms;
  };

  map::Map* map = nullptr;  // not owned
  std::vector<Segment> segments{};

  std::vector<CheckpointHit> checkpoint_hits;
  // time since the beginning of the trace for each checkpoint hit [ms]
  // first element is by definition 0
  std::vector<int32_t> checkpoint_t_ms;
};
