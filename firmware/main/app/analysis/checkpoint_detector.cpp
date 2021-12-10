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
  segments_.reserve(num_checkpoints_);
  centers_ = Eigen::Matrix2Xf::Zero(2, num_checkpoints_);
  for (int i = 0; i < num_checkpoints_; i++) {
    const auto* checkpoint = checkpoints[i];
    const Eigen::Vector2f center = math::ToEigen(*checkpoint->position());
    const float heading = math::DegToRad(checkpoint->heading_deg());
    const float half_width = checkpoint->width() * 0.5f;
    const Eigen::Vector2f center_to_left{-sin(heading) * half_width, cos(heading) * half_width};
    const Eigen::Vector2f left{center + center_to_left};
    const Eigen::Vector2f right{center - center_to_left};
    segments_.emplace_back(left, right);
    centers_.col(i) = center;

    fmt::print(
        "({:.2f},{:.2f}) -- ({:.2f},{:.2f}) -- ({:.2f},{:.2f})\n",
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
  // TODO(summivox): filter by speed
  for (int i = 0; i < num_checkpoints_; i++) {
    const auto* checkpoint = (*map_->checkpoints())[i];
    if ((curr_p - centers_.col(i)).squaredNorm() > kMaxSqrDistanceToCenterM2) {
      continue;
    }
    const float course_deg = math::RadToDeg(std::atan2(step.dir().y(), step.dir().x()));
    const float course_min_deg = checkpoint->heading_deg() - checkpoint->heading_tolerance_deg();
    const float course_max_deg = checkpoint->heading_deg() + checkpoint->heading_tolerance_deg();
    if (!(course_min_deg <= course_deg && course_deg <= course_max_deg)) {
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
