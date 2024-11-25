// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cmath>
#include <type_traits>

#include "Eigen/Core"
#include "Eigen/Geometry"

#include "math/polyfill.hpp"
#include "math/segment2.hpp"
#include "math/utils.hpp"

namespace math {

template <typename TFloat>
class Polyline2 {
 public:
  Polyline2() : points_(2, 0) {}
  template <typename TFloatOther>
  Polyline2(Eigen::Ref<const Eigen::Matrix<TFloatOther, 2, -1>> points) : points_(points.cast()) {}

  template <typename TFloatOther>
  Polyline2(const Polyline2<TFloatOther>& other) : points_(other.points_.cast()) {}
  Polyline2(Polyline2<TFloat>&& other) = default;
  template <typename TFloatOther>
  Polyline2<TFloat>& operator=(const Polyline2<TFloatOther>& other) {
    points_ = other.points_.cast();
    return *this;
  }
  Polyline2<TFloat>&& operator=(Polyline2<TFloat>&& other) = default;

 private:
  Eigen::Matrix<TFloat, 2, -1> points_;
};

using Polyline2f = Polyline2<float>;
using Polyline2d = Polyline2<double>;

}  // namespace math
