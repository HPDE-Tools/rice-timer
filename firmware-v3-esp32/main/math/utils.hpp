// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cmath>

#include "Eigen/Core"
#include "Eigen/Geometry"

namespace math {

template <class T>
constexpr T Sqr(const T& x) {
  return x * x;
}

// https://www.boost.org/doc/libs/1_75_0/libs/math/doc/html/math_toolkit/sign_functions.html
template <class TFloat>
constexpr int Sign(const TFloat& z) {
  return (z == 0) ? 0 : std::signbit(z) ? -1 : 1;
}

template <class TFloat>
constexpr TFloat Cross2(const Eigen::Vector2<TFloat>& a, const Eigen::Vector2<TFloat>& b) {
  return a.x() * b.y() - b.x() * a.y();
}

template <typename T>
constexpr T kGravity{9.80665};

template <typename T>
constexpr T kRadInDeg{180.0 / M_PI};
template <typename T>
constexpr T kDegInRad{M_PI / 180.0};

template <typename T>
constexpr T RadToDeg(T rad) {
  return rad * kRadInDeg<T>;
}
template <typename T>
constexpr T DegToRad(T deg) {
  return deg * kDegInRad<T>;
}

// clang-format off
//
// Notes on yaw-pitch-roll convention of a rotation
//
// Ranges:
//   yaw    (-pi, +pi]
//   pitch  [-pi/2, +pi/2]
//   roll   (-pi, +pi]
//
// Rotation matrix equation:
//   R(yaw, Z) * R(pitch, Y) * R(roll, X) === Composed Rotation
//
// From rotation to yaw-pitch-roll:
//   (cp = cos(pitch), sy = sin(roll), ...)
//
//   euler-derived matrix                             =  quaternion-derived matrix
//   { cp cy   cy sp sr - cr sy   cr cy sp + sr sy  }   { +w2+x2-y2-z2   2(xy-zw)       2(xz-yw)     }
//   { cp sy   cr cy + sp sr sy   -cy sr + cr sp sy } = { 2(xy+zw)       +w2-x2+y2-z2   2(yz-xw)     }
//   { -sp     cp sr              cp cr             }   { 2(xz-yw)       2(yz+xw)       +w2-x2-y2+z2 }
//
//   yaw   = atan2(cp sy, cp cy) = atan2(2(xy+zw), +w2+x2-y2-z2)
//   pitch = asin(sp)            = asin(-2(xz-yw))               = asin(2(yw-xz))
//   roll  = atan2(cp sr, cp cr) = atan2(2(yz+xw), +w2-x2-y2+z2)
//
// To avoid non-unit quaternion screwing things up, pitch can also be reformulated to atan2 (equivalent):
//   pitch = atan2(sp, cp) = atan2(sp, hypot(cp cy, cp sy)) = atan2(2(yw-xz), hypot(+w2+x2-y2-z2, 2(xy+zw)))
//   pitch = atan2(sp, cp) = atan2(sp, hypot(cp cr, cp sr)) = atan2(2(yw-xz), hypot(+w2-x2-y2+z2, 2(yz+xw)))
//
// Intuitively: Consider the "rover frame" (front, left, top) in the "world frame" (east, north, up).
// Project Rover X to World X-Y:
//   The polar angle of the projected vector (in World X-Y) is the yaw (heading).
//   The directed angle from Rover X to the projected vector is the pitch.
//
//   Roll can be derived from the yaw of the inverse transform ( (Rz Ry Rx)^-1 = Rx^-1 Ry^-1 Rz^-1 )
//   through variable substitution (admittedly not very intuitive, but the math does add up)
//
// References:
//   https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
//   http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
//     NOTE: This has a different coordinate system convention (= variable substitution), but the idea is the same.
//
// clang-format on

template <typename TFloat>
TFloat QToYaw(const Eigen::Quaternion<TFloat>& q) {
  return std::atan2(
      2 * (q.x() * q.y() + q.z() + q.w()),
      q.w() * q.w() + q.x() * q.x() - q.y() * q.y() - q.z() * q.z());
}

template <typename TFloat>
TFloat QToPitch(const Eigen::Quaternion<TFloat>& q) {
  const TFloat pitch = std::atan2(
      2 * (q.y() * q.w() - q.x() * q.z()),
      std::hypot(
          q.w() * q.w() - q.x() * q.x() - q.y() * q.y() + q.z() * q.z(),
          2 * (q.y() * q.z() + q.x() * q.w())));
  return std::clamp(pitch, -M_PI / 2, M_PI / 2);
}

template <typename TFloat>
TFloat QToRoll(const Eigen::Quaternion<TFloat>& q) {
  return std::atan2(
      2 * (q.y() * q.z() + q.x() * q.w()),
      q.w() * q.w() - q.x() * q.x() - q.y() * q.y() + q.z() * q.z());
}

}  // namespace math
