// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "interface/localization.hpp"

namespace l10n {

class Localizer {
 public:
  static Localizer* GetInstance();

  void UpdateGps(const GpsPose& gps_pose);
  void UpdateImu(const ImuReading& imu_raw);

 private:
  Localizer();
};

}  // namespace l10n
