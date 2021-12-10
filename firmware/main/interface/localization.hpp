// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>

#include "Eigen/Core"
#include "Eigen/Geometry"

/// GPS pose of the rover in WGS84 lat-long-height
struct GpsPose {
  int64_t timestamp_ms = 0;                             // time since unix epoch [ms]
  Eigen::Vector3d llh = Eigen::Vector3d::Zero();        // lat [deg], long [deg], height [m]
  Eigen::Vector3f sigma_llh = Eigen::Vector3f::Zero();  // 1-sigma error for lat-long-height
  float speed = 0;                                      // speed-over-ground [m/s]
  float course = 0;                                     // course-over-ground (north-CW) [deg]
  float heading = 0;                                    // heading of the rover (north-CW) [deg]
};

/// Raw IMU reading (in IMU local frame), scaled to SI units
struct ImuReading {
  uint32_t capture = 0;                         // TODO --- consider passing this out-of-band
  Eigen::Vector3f a = Eigen::Vector3f::Zero();  // acceleration (ax, ay, az) [m/s^2]
  Eigen::Vector3f w = Eigen::Vector3f::Zero();  // angular velocity (wx, wy, wz) [rad/s]
};

/// Pose of the rover in the local easting-northing-height coordinate system of the current map
struct MapLocalPose {
  int64_t timestamp_ms = 0;                               // time since unix epoch [ms]
  Eigen::Vector3f enh = Eigen::Vector3f::Zero();          // position in the ENH frame [m]
  Eigen::Vector3f v_enh = Eigen::Vector3f::Zero();        // velocity along the ENH frame [m/s]
  Eigen::Quaternionf q = Eigen::Quaternionf::Identity();  // rotation from the ENH frame
};
