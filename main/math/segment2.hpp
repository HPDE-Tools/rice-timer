// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cmath>
#include <type_traits>

#include "Eigen/Core"
#include "Eigen/Geometry"

#include "math/polyfill.hpp"
#include "math/utils.hpp"

namespace math {

template <typename TFloat>
class Segment2 {
 public:
  static_assert(std::is_floating_point_v<TFloat>);

  Segment2() {}
  Segment2(const Eigen::Vector2<TFloat>& a, const Eigen::Vector2<TFloat>& b)
      : a_(a), b_(b), dir_((b_ - a_).normalized()) {}

  template <typename TFloatOther>
  Segment2(const Segment2<TFloatOther>& other)
      : a_(other.a_.cast()), b_(other.b_.cast()), dir_(other.dir_.cast()) {}

  template <typename TFloatOther>
  Segment2<TFloat>& operator=(const Segment2<TFloatOther>& other) {
    a_ = other.a_.cast();
    b_ = other.b_.cast();
    dir_ = other.dir_.cast();
  }

  Eigen::Vector2<TFloat> Vec() const { return b_ - a_; }
  Eigen::Vector2<TFloat> NormalDir() const { return {-dir_.y(), dir_.x()}; }

  Eigen::Vector2<TFloat> LerpRatio(TFloat ratio) const {
    return {std::lerp(a_.x(), b_.x(), ratio), std::lerp(a_.y(), b_.y(), ratio)};
  }
  Eigen::Vector2<TFloat> LerpLength(TFloat length) const { return a_ + dir_ * length; }

  double NormSqr() const { return (b_ - a_).squaredNorm(); }
  double Norm() const { return (b_ - a_).norm(); }

  const Eigen::Vector2<TFloat>& a() const { return a_; }
  const Eigen::Vector2<TFloat>& b() const { return b_; }
  const Eigen::Vector2<TFloat>& dir() const { return dir_; }

 private:
  Eigen::Vector2<TFloat> a_{};
  Eigen::Vector2<TFloat> b_{};
  Eigen::Vector2<TFloat> dir_{};

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

template <typename TFloat>
bool IsParallel(const Segment2<TFloat>& s1, const Segment2<TFloat>& s2) {
  return std::abs(Cross2(s1.dir(), s2.dir())) <= std::numeric_limits<TFloat>::epsilon();
}

template <typename TFloat>
bool Intersect(
    const Segment2<TFloat>& s1,
    const Segment2<TFloat>& s2,
    TFloat* out_ratio1 = nullptr,
    TFloat* out_ratio2 = nullptr,
    Eigen::Vector2<TFloat>* out_point = nullptr) {
  constexpr TFloat kEps = std::numeric_limits<TFloat>::epsilon();

  // colinear will also fail
  if (IsParallel(s1, s2)) {
    return false;
  }

  const auto& a = s1.a();
  const auto& b = s1.b();
  const auto& c = s2.a();
  const auto& d = s2.b();

  // signed distance from s1 (AB) to C, D
  const TFloat abc = Cross2(s1.dir(), (c - a).eval());
  const TFloat abd = Cross2(s1.dir(), (d - a).eval());
  if (Sign(abc) * Sign(abd) > 0) {
    return false;
  }

  // signed distance from s2 (CD) to A, B
  const TFloat cda = Cross2(s2.dir(), (a - c).eval());
  const TFloat cdb = Cross2(s2.dir(), (b - c).eval());
  if (Sign(cda) * Sign(cdb) > 0) {
    return false;
  }

  // use similar triangles to calculate intersection
  // NOTE(summivox): order below is CORRECT
  const TFloat base1 = cda - cdb;
  const TFloat base2 = abc - abd;
  const TFloat ratio1 = cda / base1;
  const TFloat ratio2 = abc / base2;
  if (!(-kEps <= ratio1 && ratio1 <= TFloat{1.0} + kEps)) {
    return false;
  }
  if (!(-kEps <= ratio2 && ratio2 <= TFloat{1.0} + kEps)) {
    return false;
  }
  if (out_ratio1) {
    *out_ratio1 = ratio1;
  }
  if (out_ratio2) {
    *out_ratio2 = ratio2;
  }
  if (out_point) {
    if (std::abs(base1) > std::abs(base2)) {
      *out_point = s1.LerpRatio(ratio1);
    } else {
      *out_point = s2.LerpRatio(ratio2);
    }
  }
  return true;
}

using Segment2f = Segment2<float>;
using Segment2d = Segment2<double>;

}  // namespace math
