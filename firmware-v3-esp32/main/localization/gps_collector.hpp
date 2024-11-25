// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <optional>

#include "minmea.h"

#include "device/gps_utils.hpp"
#include "interface/localization.hpp"

namespace l10n {

class GpsCollector {
 public:
  GpsCollector() = default;

  void Reset();
  bool StartCalibration();
  std::optional<GpsPose> Update(const ParsedNmea& nmea);

 private:
  uint32_t expected_ = MINMEA_SENTENCE_RMC | MINMEA_SENTENCE_GGA | MINMEA_SENTENCE_GST;
  uint32_t received_ = 0u;
  std::optional<minmea_time> group_time_;
  GpsPose pose_;
};

}  // namespace l10n
