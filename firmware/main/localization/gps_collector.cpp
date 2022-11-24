// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "localization/gps_collector.hpp"

#include "common/macros.hpp"
#include "common/utils.hpp"
#include "device/gps_utils.hpp"

namespace l10n {

namespace {
constexpr char TAG[] = "l10n/gps";
}

void GpsCollector::Reset() {
  received_ = 0u;
  group_time_.reset();
  pose_ = {};
}

bool GpsCollector::StartCalibration() {
  // TODO: actually enter calibration mode (consider auto-exit too)
  expected_ = MINMEA_SENTENCE_RMC | MINMEA_SENTENCE_GGA | MINMEA_SENTENCE_GST;
  return true;
}

std::optional<GpsPose> GpsCollector::Update(const ParsedNmea& nmea) {
  using namespace std::rel_ops;
  std::optional<GpsPose> result{};

  const std::optional<minmea_time> time_of_day = GetTimeOfDayFromNmea(nmea);
  if (time_of_day) {
    if (group_time_) {
      if (*time_of_day != *group_time_) {
        result = pose_;
        Reset();
        return result;
      }
    } else {
      group_time_ = time_of_day;
    }
  }

  pose_.is_valid = true;
  std::visit(
      overloaded{
          [this](const minmea_sentence_rmc& rmc) {
            ESP_LOGW(TAG, "(%d,%d)", rmc.latitude.value, rmc.longitude.value);
            const auto timestamp = GetTimestampFromMinmeaDateTime(rmc.date, rmc.time);
            if (timestamp) {
              pose_.timestamp_ms = ToMilliseconds(*timestamp);
            }
            pose_.llh[0] = minmea_tocoord(&rmc.latitude);
            pose_.llh[1] = minmea_tocoord(&rmc.longitude);
            pose_.speed_knot = minmea_tofloat(&rmc.speed);
            pose_.course_north_cw_deg = minmea_tofloat(&rmc.course);
            if (!rmc.valid) {
              pose_.is_valid = false;
            }
            received_ |= MINMEA_SENTENCE_RMC;
          },
          [this](const minmea_sentence_gga& gga) {
            // (Antenna height above ellipsoid) = (Antenna altitude above geoid) +
            //                                    (Geoid height above ellipsoid)
            // See: https://gis.stackexchange.com/a/174116
            pose_.llh[2] = minmea_tofloat(&gga.altitude) + minmea_tofloat(&gga.height);
            received_ |= MINMEA_SENTENCE_GGA;
          },
          [this](const minmea_sentence_gst& gst) {
            // clang-format off
            pose_.sigma_llh <<
                minmea_tofloat(&gst.latitude_error_deviation),
                minmea_tofloat(&gst.longitude_error_deviation),
                minmea_tofloat(&gst.altitude_error_deviation);
            // clang-format on
            received_ |= MINMEA_SENTENCE_GST;
          },
          [](const auto&) {},
      },
      nmea);

  if ((received_ & expected_) == expected_) {
    result = pose_;
    Reset();
  }
  return result;
}

}  // namespace l10n
