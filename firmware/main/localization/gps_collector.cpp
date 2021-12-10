// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "localization/gps_collector.hpp"

#include "common/macros.hpp"
#include "common/utils.hpp"
#include "device/gps_utils.hpp"

namespace l10n {

void GpsCollector::Reset() {
  group_ = 0u;
  group_time_.reset();
  result_ = {};
}

bool GpsCollector::StartCalibration() {
  // TODO: actually enter calibration mode (consider auto-exit too)
  group_mask_ = MINMEA_SENTENCE_RMC | MINMEA_SENTENCE_GGA | MINMEA_SENTENCE_GST;
  return true;
}

std::optional<GpsPose> GpsCollector::Update(const ParsedNmea& nmea) {
  using namespace std::rel_ops;
  std::optional<GpsPose> result{};

  const std::optional<minmea_time> time_of_day = GetTimeOfDayFromNmea(nmea);
  if (time_of_day) {
    if (group_time_) {
      if (*time_of_day != *group_time_) {
        result = result_;
        Reset();
        return result;
      }
    } else {
      group_time_ = time_of_day;
    }
  }

  std::visit(
      overloaded{
          [this](const minmea_sentence_rmc& rmc) {
            const auto timestamp = GetTimestampFromMinmeaDateTime(rmc.date, rmc.time);
            if (timestamp) {
              result_.timestamp_ms = ToMilliseconds(*timestamp);
            }
            result_.llh[0] = minmea_tocoord(&rmc.latitude);
            result_.llh[1] = minmea_tocoord(&rmc.longitude);
            group_ |= MINMEA_SENTENCE_RMC;
          },
          [this](const minmea_sentence_gga& gga) {
            // (Antenna height above ellipsoid) = (Antenna altitude above geoid) +
            //                                    (Geoid height above ellipsoid)
            // See: https://gis.stackexchange.com/a/174116
            result_.llh[2] = minmea_tofloat(&gga.altitude) + minmea_tofloat(&gga.height);
            group_ |= MINMEA_SENTENCE_GGA;
          },
          [this](const minmea_sentence_gst& gst) {
            // clang-format off
            result_.sigma_llh <<
                minmea_tofloat(&gst.latitude_error_deviation),
                minmea_tofloat(&gst.longitude_error_deviation),
                minmea_tofloat(&gst.altitude_error_deviation);
            // clang-format on
            group_ |= MINMEA_SENTENCE_GST;
          },
          [](const auto&) {},
      },
      nmea);

  if ((group_ & group_mask_) == group_mask_) {
    result = result_;
    Reset();
  }
  return result;
}

}  // namespace l10n
