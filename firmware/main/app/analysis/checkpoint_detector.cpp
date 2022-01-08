// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/analysis/checkpoint_detector.hpp"

#include <cmath>

#include "fmt/core.h"

#include "math/proto.hpp"
#include "math/utils.hpp"

namespace analysis {

CheckpointDetector::CheckpointDetector() {}

CheckpointDetector::CheckpointDetector(const map::Map* map) { SetMap(map); }

void CheckpointDetector::SetMap(const map::Map* map) {
  map_ = map;
  if (!map || !map->checkpoints()) {
    return;
  }
  const auto& checkpoints = *map->checkpoints();
  num_checkpoints_ = checkpoints.size();
  segments_.clear();
  segments_.reserve(num_checkpoints_);
  centers_.resize(2, num_checkpoints_);
  course_range_rad_.resize(2, num_checkpoints_);
  for (int i = 0; i < num_checkpoints_; i++) {
    const auto* checkpoint = checkpoints[i];
    const Eigen::Vector2f center = math::ToEigen(*checkpoint->position());
    const float heading = math::DegToRad(checkpoint->heading_deg());
    const float heading_tol = math::DegToRad(checkpoint->heading_tolerance_deg());
    const float width_left =
        checkpoint->width_left() > 0 ? checkpoint->width_left() : checkpoint->width() * 0.5f;
    const float width_right =
        checkpoint->width_right() > 0 ? checkpoint->width_right() : checkpoint->width() * 0.5f;
    const Eigen::Vector2f center_to_left_dir{-sin(heading), cos(heading)};
    const Eigen::Vector2f left{center + center_to_left_dir * width_left};
    const Eigen::Vector2f right{center - center_to_left_dir * width_right};

    segments_.emplace_back(left, right);
    centers_.col(i) = center;
    course_range_rad_.col(i) << heading - heading_tol, heading + heading_tol;

    fmt::print(
        "[{}] : ({:.2f},{:.2f}) -- ({:.2f},{:.2f}) -- ({:.2f},{:.2f})\n",
        i,
        left.x(),
        left.y(),
        center.x(),
        center.y(),
        right.x(),
        right.y());  // DEBUG
  }
}

std::optional<CheckpointDetector::Result> CheckpointDetector::Detect(
    const CircularBuffer<MapLocalPose>& pose_history) {
  std::optional<Result> result{};
  if (pose_history.size() <= 2) {
    return result;
  }
  const MapLocalPose& curr_pose = pose_history[-1];
  const MapLocalPose& last_pose = pose_history[-2];
  const Eigen::Vector2f curr_p = curr_pose.enh.head<2>();
  const Eigen::Vector2f last_p = last_pose.enh.head<2>();
  const math::Segment2f step{last_p, curr_p};
  const float course_rad = std::atan2(step.dir().y(), step.dir().x());
  // TODO(summivox): filter by speed
  for (int i = 0; i < num_checkpoints_; i++) {
    if ((curr_p - centers_.col(i)).squaredNorm() > kMaxSqrDistanceToCenterM2) {
      continue;
    }
    if (!(course_range_rad_(0, i) <= course_rad && course_rad <= course_range_rad_(1, i))) {
      continue;
    }

    float step_ratio = NAN;
    if (math::Intersect(
            segments_[i],
            step,
            /*ratio1*/ (float*)nullptr,
            &step_ratio,
            /*point*/ (Eigen::Vector2f*)nullptr)) {
      result.emplace();
      result->timestamp_ms = last_pose.timestamp_ms +
                             static_cast<int64_t>(std::round(
                                 (curr_pose.timestamp_ms - last_pose.timestamp_ms) * step_ratio));
      result->checkpoint_index = i;
      break;
    }
  }
  return result;
}

}  // namespace analysis
