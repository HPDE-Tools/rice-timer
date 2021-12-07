// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>

#include "Eigen/Core"
#include "Eigen/Geometry"

/// GPS pose of the rover in WGS84 lat-long-height
struct GpsPose {
  int64_t timestamp_ms;       // time since unix epoch [ms]
  Eigen::Vector3f llh;        // lat [deg], long [deg], height [m]
  Eigen::Vector3f sigma_llh;  // 1-sigma error for lat-long-height
  float speed;                // speed-over-ground [m/s]
  float course;               // course-over-ground relative to GNSS north [deg]
  float heading;              // heading of the rover relative to GNSS north [deg]
};

/// Raw IMU reading (in IMU local frame), scaled to SI units
struct ImuReading {
  uint32_t capture;   //
  Eigen::Vector3f a;  // acceleration (ax, ay, az) [m/s^2]
  Eigen::Vector3f w;  // angular velocity (wx, wy, wz) [rad/s]
};

/// Pose of the rover in the local easting-northing-height coordinate system of the current map
struct MapLocalPose {
  Eigen::Vector3f enh;    // position in the ENH frame [m]
  Eigen::Vector3f v_enh;  // velocity along the ENH frame [m/s]
  Eigen::Quaternionf q;   // rotation from the ENH frame
};
