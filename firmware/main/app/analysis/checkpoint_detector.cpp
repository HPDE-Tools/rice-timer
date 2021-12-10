// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/analysis/checkpoint_detector.hpp"

namespace analysis {

CheckpointDetector::CheckpointDetector() {}

CheckpointDetector::CheckpointDetector(const map::Map* map) : map_(map) {}

std::optional<CheckpointDetector::Detection> CheckpointDetector::Detect(const MapLocalPose& pose) {
  return {};  // TODO
}

}  // namespace analysis
