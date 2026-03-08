// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "Eigen/Core"
#include <cmath>

namespace map {

// Earth radius in meters (WGS84 mean radius)
inline constexpr double kEarthRadiusM = 6378137.0;

/**
 * Calculate the great-circle distance between two lat/lon points using Haversine formula.
 * @param a First point as (lat, lon) in radians
 * @param b Second point as (lat, lon) in radians
 * @return Distance in meters
 */
inline double GeodesicDistance(const Eigen::Vector2d& a, const Eigen::Vector2d& b) {
  // Convert degrees to radians
  const double lat1 = a[0] * M_PI / 180.0;
  const double lon1 = a[1] * M_PI / 180.0;
  const double lat2 = b[0] * M_PI / 180.0;
  const double lon2 = b[1] * M_PI / 180.0;

  const double dlat = lat2 - lat1;
  const double dlon = lon2 - lon1;

  const double sin_dlat_2 = std::sin(dlat * 0.5);
  const double sin_dlon_2 = std::sin(dlon * 0.5);

  const double a_val = sin_dlat_2 * sin_dlat_2 +
                       std::cos(lat1) * std::cos(lat2) * sin_dlon_2 * sin_dlon_2;

  return 2.0 * kEarthRadiusM * std::atan2(std::sqrt(a_val), std::sqrt(1.0 - a_val));
}

}  // namespace map
