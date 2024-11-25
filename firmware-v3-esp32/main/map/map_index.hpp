// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <string>
#include <string_view>
#include <utility>

#include "Eigen/Core"
#include "esp_err.h"

#include "common/mutex.hpp"
#include "proto/map_generated.h"

namespace map {

class MapIndex {
 public:
  using MapType = ricetimer::proto::MapType;
  struct Entry {
    std::string path;
    std::string name;
    Eigen::Vector2d origin_latlon;
    MapType type;
  };

  friend class RustMutex<MapIndex>;
  static RustMutexGuard<MapIndex> GetInstance();

  const std::vector<Entry>& entries() const { return entries_; }

  esp_err_t Load(std::string_view map_data_path);

  /// Finds the map whose origin is the closest to the given point.
  /// \returns {basic info of the map, distance of this map to input point}
  std::pair<const Entry*, double> GetNearestMap(const Eigen::Vector2d& latlon);

 private:
  std::string map_data_path_;

  std::vector<Entry> entries_;

  SemaphoreHandle_t mutex_{};

  MapIndex();
};

}  // namespace map
