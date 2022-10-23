// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/gps_daemon.hpp"

#include <sys/time.h>
#include <time.h>
#include <cinttypes>
#include <string_view>

#include "driver/uart.h"
#include "fmt/chrono.h"
#include "fmt/compile.h"
#include "fmt/core.h"
#include "minmea.h"

#include "common/macros.hpp"
#include "common/perishable.hpp"
#include "common/strings.hpp"
#include "common/times.hpp"
#include "common/utils.hpp"
#include "device/capture_manager.hpp"
#include "device/gps_utils.hpp"
#include "io/autobaud.hpp"
#include "ui/model.hpp"

namespace {

constexpr char TAG[] = "gpsd";

constexpr int kGpsStackSize = 6000;
constexpr int kGpsPollMs = 10;

constexpr int kMinPpsToGpsOffsetMs = -50;
constexpr int kMaxPpsToGpsOffsetMs = 250;

constexpr int kMaxAdjustableDeltaTimeSec = 2 * 60 * 60;

}  // namespace

using std::nullopt;

GpsDaemon::GpsDaemon(
    io::UartLineReader* line_reader, CaptureManager* capture_manager, Option option)
    : option_(option),
      line_reader_(CHECK_NOTNULL(line_reader)),
      capture_manager_(CHECK_NOTNULL(capture_manager)),
      sw_capture_(capture_manager->GetChannel(option.software_capture_signal)),
      century_(option.century) {}

esp_err_t GpsDaemon::Setup() {
  TRY(capture_manager_->Subscribe(
      option_.pps_capture_signal,
      MCPWM_POS_EDGE,
      0,
      [this](
          mcpwm_unit_t /*unit*/,
          mcpwm_capture_signal_t /*signal*/,
          uint32_t /*edge*/,
          uint32_t value) { PpsCaptureIsr(value); }));
  return ESP_OK;
}

GpsDaemon::~GpsDaemon() {
  Stop();
  capture_manager_->Unsubscribe(option_.pps_capture_signal);
}

esp_err_t GpsDaemon::Start(
    GpsSetupHandler setup_handler,
    GpsStateChangeSubscriber&& state_change_subscriber,
    GpsDataSubscriber&& data_subscriber,
    GpsRawLineSubscriber&& line_subscriber) {
  state_ = kLost;
  setup_handler_ = setup_handler;
  state_change_subscriber_ = state_change_subscriber;
  data_subscriber_ = data_subscriber;
  line_subscriber_ = line_subscriber;
  latest_pps_.Reset();
  latest_gps_.Reset();
  return Task::SpawnSame(TAG, kGpsStackSize, option_.priority);
}

void GpsDaemon::Stop() {
  Task::Kill();
  latest_pps_.Reset();
  latest_gps_.Reset();
  setup_handler_ = nullptr;
  data_subscriber_ = nullptr;
  line_subscriber_ = nullptr;
  state_ = kLost;
}

void GpsDaemon::PpsCaptureIsr(uint32_t value) {
  latest_pps_.Set(value, xTaskGetTickCountFromISR());
}

void GpsDaemon::DebugPrintState() {
  static TickType_t last_print = xTaskGetTickCount();
  if (SignedMinus(xTaskGetTickCount(), last_print) >= pdMS_TO_TICKS(1000)) {
    last_print = xTaskGetTickCount();
    ESP_LOGV(TAG, "state=%d", (int)state_);
  }
}

void GpsDaemon::Run() {
  static const TickType_t gps_timeout = pdMS_TO_TICKS(option_.gps_timeout_ms);
  static const TickType_t pps_timeout = pdMS_TO_TICKS(option_.pps_timeout_ms);

  static ParsedNmea nmea;

  ChangeState(kLost);
  while (true) {
    DebugPrintState();
    if (state_ == kLost) {
      if (setup_handler_(line_reader_)) {
        ESP_LOGI(TAG, "device-specific setup successful");
        ChangeState(kAwaitingNmea);
        latest_pps_.Reset();
        latest_gps_.Set(ESP_ERR_NOT_FOUND, xTaskGetTickCount());
        line_reader_->DiscardInputBuffer();
      } else {
        ESP_LOGW(TAG, "device-specific setup fail");
        vTaskDelay(pdMS_TO_TICKS(option_.setup_retry_ms));
      }
      continue;
    }

    // Each poll cycle we only wait for a short time, so that we could check for both PPS and GPS
    // stale condition and react accordingly.
    if (!line_reader_->ReadOneLineInto(line_buf_, pdMS_TO_TICKS(kGpsPollMs))) {
      line_buf_.clear();
    }
    const TickType_t now_ostime = xTaskGetTickCount();
    const auto latest_pps = latest_pps_.Check(now_ostime, pps_timeout);

    // Timing-sensitive steps have all been done; from here onwards we no longer need to worry about
    // blocking (too much).

    nmea = ParseNmea(line_buf_);
    // NOTE: parsed: we have converted the line to one of the minmea_sentence_xxx structs;
    //       valid: the line is valid NMEA, but we don't know how to parse it.
    const bool nmea_is_parsed = !std::holds_alternative<esp_err_t>(nmea);
    const bool nmea_is_valid = nmea_is_parsed || std::get<esp_err_t>(nmea) == ESP_ERR_NOT_SUPPORTED;
    if (nmea_is_valid) {
      latest_gps_.Set(nmea, now_ostime);
    } else if (!latest_gps_.Check(now_ostime, gps_timeout)) {
      ESP_LOGE(TAG, "GPS timeout");
      ChangeState(kLost);
      continue;
    }

    std::optional<GpsTimeFix> time_fix;
    if (latest_pps) {
      time_fix = TryMatchPpsGps(latest_pps->data, latest_pps->time, now_ostime, nmea);
      if (time_fix) {
        AdjustSystemTime(*time_fix, sw_capture_);
        had_first_fix_ = true;
        initialized_system_time_ = true;
      }
    } else if (nmea_is_parsed && !initialized_system_time_) {
      // try to at least set system time coarsely (better than seconds-since-boot)
      const std::optional<TimeUnixWithUs> nmea_unix = GetTimeFromNmea(nmea);
      if (nmea_unix) {
        settimeofday(&*nmea_unix, /*tz*/ nullptr);
        initialized_system_time_ = true;
        ESP_LOGW(TAG, "settimeofday (coarse): %" PRIi64, (int64_t)nmea_unix->tv_sec);
      }
    }

    switch (state_) {
      case kAwaitingNmea: {
        if (time_fix) {
          ChangeState(kActive);
        } else if (nmea_is_valid) {
          ChangeState(kAwaitingTimeFix);
        }
      } break;
      case kAwaitingTimeFix: {
        if (time_fix) {
          ChangeState(kActive);
        }
      } break;
      case kActive: {
        if (!latest_pps) {
          ChangeState(kAwaitingTimeFix);
        }
      } break;
      default:
        CHECKED_UNREACHABLE;
    }

    if (line_subscriber_ && !line_buf_.empty()) {
      line_subscriber_(line_buf_, nmea_is_valid);
    }
    if (data_subscriber_ && nmea_is_valid) {
      data_subscriber_(state_, nmea, time_fix);
    }
  }  // while (true)
}

void GpsDaemon::ChangeState(GpsDaemon::State state) {
  state_ = state;
  if (state_change_subscriber_) {
    state_change_subscriber_(state);
  }
}

std::optional<GpsTimeFix> GpsDaemon::TryMatchPpsGps(
    uint32_t pps_capture, TickType_t pps_ostime, TickType_t gps_ostime, const ParsedNmea& nmea) {
  const std::optional<TimeUnixWithUs> nmea_unix = GetTimeFromNmea(nmea);
  if (!(nmea_unix && nmea_unix->tv_usec == 0)) {
    return {};
  }
  const int pps_to_gps_delay = SignedMinus(gps_ostime, pps_ostime);
  constexpr int kMin = kMinPpsToGpsOffsetMs / int(portTICK_PERIOD_MS);
  constexpr int kMax = kMaxPpsToGpsOffsetMs / int(portTICK_PERIOD_MS);
  if (!(kMin <= pps_to_gps_delay && pps_to_gps_delay <= kMax)) {
    ESP_LOGW(
        TAG,
        "t_gps - t_pps = %+d ticks => too large (min %+d, max %+d)",
        pps_to_gps_delay,
        kMin,
        kMax);
    return {};
  }
  return GpsTimeFix{
      .pps_capture = pps_capture,
      .pps_ostime = pps_ostime,
      .gps_ostime = gps_ostime,
      .parsed_time_unix = nmea_unix->tv_sec,
  };
}

void GpsDaemon::AdjustSystemTime(const GpsTimeFix& time_fix, const CaptureChannel& sw_capture) {
  // 1 us => how many capture ticks? (this should only ever need to be set once)
  static const int kCaptureTicksInUs = sw_capture.GetNominalFreqHz() / 1'000'000;

  TimeUnixWithUs system_now{};
  gettimeofday(&system_now, /*tz*/ nullptr);
  const uint32_t capture_now = sw_capture.TriggerNow();

  const time_t a_s = system_now.tv_sec;
  const suseconds_t a_us = system_now.tv_usec;
  const time_t b_s = time_fix.parsed_time_unix;
  const int32_t b_us = SignedMinus(capture_now, time_fix.pps_capture) / kCaptureTicksInUs;
  const auto d_s = b_s - a_s;
  const auto d_us = b_us - a_us;

  ESP_LOGV(
      TAG,
      "sys=%" PRIi64 ".%06" PRIi64 " gps=%" PRIi64 ".%06" PRIi64 " ds=%" PRIi64 " dus=%" PRIi64,
      static_cast<int64_t>(a_s),
      static_cast<int64_t>(a_us),
      static_cast<int64_t>(b_s),
      static_cast<int64_t>(b_us),
      static_cast<int64_t>(d_s),
      static_cast<int64_t>(d_us));

  if (std::abs(d_s) >= kMaxAdjustableDeltaTimeSec) {
    const TimeUnixWithUs nmea_unix{.tv_sec = b_s, .tv_usec = b_us};
    settimeofday(&nmea_unix, /*tz*/ nullptr);
    ESP_LOGW(
        TAG,
        "settimeofday: %" PRIi64 " -> %" PRIi64,
        static_cast<int64_t>(a_s),
        static_cast<int64_t>(b_s));
  } else {
    TimeUnixWithUs delta{.tv_sec = d_s, .tv_usec = d_us};
    adjtime(&delta, /*old_delta*/ nullptr);
  }
}
