// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "localization/localizer.hpp"

#include "Eigen/Core"
#include "Eigen/Geometry"

#include "common/macros.hpp"
#include "map/map.hpp"
#include "math/utils.hpp"

namespace l10n {

Localizer::Localizer() {}
Localizer::Localizer(const map::Map* map) { SetMap(map); }

void Localizer::Reset() { last_gps_pose_.reset(); }
void Localizer::SetMap(const map::Map* map) {
  map_ = map;
  Reset();
}

void Localizer::UpdateGps(const GpsPose& gps_pose) { last_gps_pose_ = gps_pose; }

void Localizer::UpdateImu(const ImuReading& /*imu_raw*/) {
  // NOP in trivial forwarder impl
}

MapLocalPose Localizer::Compute() {
  CHECK(map_);
  CHECK(last_gps_pose_);
  MapLocalPose result{};

  result.timestamp_ms = last_gps_pose_->timestamp_ms;

  result.enh.head<2>() = map_->LlhToLtm(last_gps_pose_->llh);
  result.enh[2] = last_gps_pose_->llh[2];

  const double speed = last_gps_pose_->speed;
  const double course = math::DegToRad(90 - last_gps_pose_->course);  // north-cw to east-ccw
  result.v_enh << speed * cos(course), speed * sin(course), 0.0;

  result.q = Eigen::AngleAxisf(course, Eigen::Vector3f::UnitZ());
  return result;
}

}  // namespace l10n
