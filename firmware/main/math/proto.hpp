// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "Eigen/Core"

#include "proto/common_generated.h"

namespace math {

Eigen::Vector2f ToEigen(const ricetimer::proto::Vec2F& proto) { return {proto.x(), proto.y()}; }
Eigen::Vector2d ToEigen(const ricetimer::proto::Vec2D& proto) { return {proto.x(), proto.y()}; }
Eigen::Vector3f ToEigen(const ricetimer::proto::Vec3F& proto) {
  return {proto.x(), proto.y(), proto.z()};
}
Eigen::Vector3d ToEigen(const ricetimer::proto::Vec3D& proto) {
  return {proto.x(), proto.y(), proto.z()};
}

}  // namespace math
