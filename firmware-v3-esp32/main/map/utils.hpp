// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "Eigen/Core"
#include "GeographicLib/Geodesic.hpp"
#include "esp_err.h"

namespace map {

inline double GeodesicDistance(const Eigen::Vector2d& a, const Eigen::Vector2d& b) {
  double distance{};
  (void)GeographicLib::Geodesic::WGS84().Inverse(a[0], a[1], b[0], b[1], distance);
  return distance;
}

}  // namespace map
