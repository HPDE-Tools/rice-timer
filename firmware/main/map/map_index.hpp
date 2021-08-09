// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <string>
#include <string_view>

#include "Eigen/Core"
#include "esp_err.h"

#include "proto/map_generated.h"

namespace map {

class MapIndex {
 public:
  using MapType = ricetimer::proto::MapType;
  struct Entry {
    std::string name;
    Eigen::Vector2d origin_latlon;
    MapType type;
  };
  static MapIndex* GetInstance();

  esp_err_t Load(std::string_view map_data_path);

 private:
  std::string map_data_path_;

  std::vector<Entry> entries_;

  MapIndex();
};

}  // namespace map
