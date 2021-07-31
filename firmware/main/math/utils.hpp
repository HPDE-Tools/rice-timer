// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cmath>

#include <Eigen/Core>

namespace math {

// https://www.boost.org/doc/libs/1_75_0/libs/math/doc/html/math_toolkit/sign_functions.html
template <class TFloat>
constexpr int Sign(const TFloat& z) {
  return (z == 0) ? 0 : std::signbit(z) ? -1 : 1;
}

template <class TFloat>
constexpr TFloat Cross2(const Eigen::Vector2<TFloat>& a, const Eigen::Vector2<TFloat>& b) {
  return a.x() * b.y() - b.x() * a.y();
}

}  // namespace math
