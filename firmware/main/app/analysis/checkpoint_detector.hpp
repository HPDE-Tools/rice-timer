// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <optional>

#include "interface/localization.hpp"
#include "map/map.hpp"

namespace analysis {

class CheckpointDetector {
 public:
  struct Detection {
    int64_t timestamp_ms;
    // TODO
  };

  CheckpointDetector();
  explicit CheckpointDetector(const map::Map* map);

  void set_map(const map::Map* map);

  std::optional<Detection> Detect(const MapLocalPose& pose);

 private:
  const map::Map* map_ = nullptr;  // not owned
};

}  // namespace analysis
