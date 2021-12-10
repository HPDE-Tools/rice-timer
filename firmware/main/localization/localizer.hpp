// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "interface/localization.hpp"

namespace map {
class Map;
}  // namespace map

namespace l10n {

class Localizer {
 public:
  Localizer();
  explicit Localizer(const map::Map* map);

  void Reset();
  void SetMap(const map::Map* map);

  void UpdateGps(const GpsPose& gps_pose);
  void UpdateImu(const ImuReading& imu_raw);

  MapLocalPose Compute();

 private:
  const map::Map* map_ = nullptr;  // not owned

  // NOTE: This is currently a trivial forwarder of GPS info
  std::optional<GpsPose> last_gps_pose_{};
};

}  // namespace l10n
