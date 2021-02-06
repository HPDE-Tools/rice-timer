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

#include "capture_manager.hpp"
#include "common/logging.hpp"
#include "common/perishable.hpp"
#include "common/scope_guard.hpp"
#include "common/strings.hpp"
#include "common/times.hpp"
#include "common/utils.hpp"
#include "device/gps_utils.hpp"
#include "io/autobaud.hpp"
#include "logger.hpp"
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
    io::UartLineReader* line_reader,
    CaptureManager* capture_manager,
    GpsSetupHandler setup_handler,
    Option option)
    : option_(option),
      line_reader_(CHECK_NOTNULL(line_reader)),
      capture_manager_(CHECK_NOTNULL(capture_manager)),
      sw_capture_(capture_manager->GetChannel(option.software_capture_signal)),
      setup_(setup_handler),
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
    GpsDataSubscriber&& data_subscriber, GpsRawLineSubscriber&& line_subscriber) {
  state_ = kLost;
  data_subscriber_ = data_subscriber;
  line_subscriber_ = line_subscriber;
  latest_pps_.Reset();
  latest_gps_.Reset();
  return Task::SpawnSame(TAG, kGpsStackSize, option_.priority);
}

void GpsDaemon::Stop() {
  Task::Kill();
  latest_gps_.Reset();
  latest_pps_.Reset();
  data_subscriber_ = nullptr;
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

  state_ = kLost;
  while (true) {
    DebugPrintState();
    if (state_ == kLost) {
      if (setup_(line_reader_)) {
        ESP_LOGI(TAG, "device-specific setup successful");
        state_ = kAwaitingNmea;
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
    const std::string line = line_reader_->ReadOneLine(pdMS_TO_TICKS(kGpsPollMs));
    const TickType_t now_ostime = xTaskGetTickCount();
    const auto latest_pps = latest_pps_.Check(now_ostime, pps_timeout);

    // Timing-sensitive steps have all been done; from here onwards we no longer need to worry about
    // blocking (too much).

    nmea = ParseNmea(line);
    const bool nmea_is_valid = !std::holds_alternative<esp_err_t>(nmea);
    if (nmea_is_valid) {
      latest_gps_.Set(nmea, now_ostime);
    } else if (!latest_gps_.Check(now_ostime, gps_timeout)) {
      ESP_LOGE(TAG, "GPS timeout");
      state_ = kLost;
      continue;
    }

    std::optional<GpsTimeFix> time_fix;
    if (latest_pps) {
      time_fix = TryMatchPpsGps(latest_pps->data, latest_pps->time, now_ostime, nmea);
      if (time_fix) {
        AdjustSystemTime(*time_fix, sw_capture_);
      }
    }

    switch (state_) {
      case kAwaitingNmea: {
        if (time_fix) {
          state_ = kActive;
        } else if (nmea_is_valid) {
          state_ = kAwaitingTimeFix;
        }
      } break;
      case kAwaitingTimeFix: {
        if (time_fix) {
          state_ = kActive;
        }
      } break;
      case kActive: {
        if (!latest_pps) {
          state_ = kAwaitingTimeFix;
        }
      } break;
      default:
        CHECK(false && "unreachable");
        break;
    }

    if (line_subscriber_ && !line.empty()) {
      line_subscriber_(line, nmea_is_valid);
    }
    if (data_subscriber_ && nmea_is_valid) {
      data_subscriber_(state_, nmea, time_fix);
    }
  }  // while (true)
}

std::optional<GpsTimeFix> GpsDaemon::TryMatchPpsGps(
    uint32_t pps_capture, TickType_t pps_ostime, TickType_t gps_ostime, const ParsedNmea& nmea) {
  minmea_date date;
  minmea_time time;
  const bool nmea_matchable = std::visit(
      overloaded{
          [&](const minmea_sentence_rmc& rmc) {
            date = rmc.date;
            time = rmc.time;
            return true;
          },
          [](const auto&) { return false; }},
      nmea);
  if (!(nmea_matchable && time.microseconds == 0)) {
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
  TimeZulu nmea_zulu = ToZulu(century_, date, time);
  const TimeUnix nmea_unix = ToUnix(nmea_zulu);
  return GpsTimeFix{
      .pps_capture = pps_capture,
      .pps_ostime = pps_ostime,
      .gps_ostime = gps_ostime,
      .parsed_time_unix = nmea_unix,
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

  ESP_LOGI(
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
