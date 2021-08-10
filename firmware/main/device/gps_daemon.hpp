// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <atomic>
#include <memory>
#include <string_view>

#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "driver/uart.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "minmea.h"
#include "soc/uart_struct.h"

#include "common/macros.hpp"
#include "common/perishable.hpp"
#include "common/task.hpp"
#include "device/capture_manager.hpp"
#include "device/gps_utils.hpp"
#include "io/uart_line_reader.hpp"

class GpsDaemon : public Task {
 public:
  struct Option {
    mcpwm_capture_signal_t pps_capture_signal = MCPWM_SELECT_CAP0;
    mcpwm_capture_signal_t software_capture_signal = MCPWM_SELECT_CAP2;

    int gps_timeout_ms = 1500;
    int pps_timeout_ms = 2500;
    int setup_retry_ms = 1000;

    int century = kBuildCentury;

    int priority = 0;
  };

  enum State {
    /// We haven't heard from GPS for a while.
    kLost,
    /// The GPS has (supposingly) been set up. We will wait for a valid incoming NMEA sentence to
    /// confirm that it's indeed alive.
    kAwaitingNmea,
    /// We have got some NMEA sentence, but none has been matched with PPS event so far.
    kAwaitingTimeFix,
    /// We have both NMEA and PPS locked in and up to date.
    kActive,
  };

  using GpsSetupHandler = std::function<bool(io::UartLineReader* line_reader)>;
  using GpsStateChangeSubscriber = std::function<void(State state)>;
  using GpsRawLineSubscriber = std::function<void(std::string_view line, bool is_valid_nmea)>;
  using GpsDataSubscriber = std::function<void(
      State state, const ParsedNmea& nmea, const std::optional<GpsTimeFix>& time_fix)>;

  virtual ~GpsDaemon();

  esp_err_t Start(
      GpsSetupHandler setup_handler,
      GpsStateChangeSubscriber&& state_change_subscriber,
      GpsDataSubscriber&& data_subscriber,
      GpsRawLineSubscriber&& line_subscriber);
  void Stop();

  IRAM_ATTR void PpsCaptureIsr(uint32_t value);

  State state() const { return state_; }
  auto latest_pps() const { return latest_pps_.Get(); }
  auto latest_gps() const { return latest_gps_.Get(); }

  /// \returns whether a precise time fix had been received
  bool had_first_fix() const { return had_first_fix_; }

  /// \returns whether the system time has been updated at all
  bool initialized_system_time() const { return initialized_system_time_; }

  DEFINE_CREATE(GpsDaemon);

 protected:
  void Run() override;

 private:
  const Option option_;
  io::UartLineReader* const line_reader_;  // not owned
  CaptureManager* const capture_manager_;  // not owned
  const CaptureChannel sw_capture_;        // derived from capture manager
  GpsSetupHandler setup_handler_;
  GpsStateChangeSubscriber state_change_subscriber_;
  GpsDataSubscriber data_subscriber_;
  GpsRawLineSubscriber line_subscriber_;

  std::atomic<State> state_ = kLost;
  Perishable</*data*/ uint32_t, /*time*/ TickType_t> latest_pps_;
  Perishable</*data*/ ParsedNmea, /*time*/ TickType_t> latest_gps_;
  bool had_first_fix_ = false;
  bool initialized_system_time_ = false;

  int century_;

  GpsDaemon(io::UartLineReader* line_reader, CaptureManager* capture_manager, Option option);

  esp_err_t Setup();
  void ChangeState(State state);
  void DebugPrintState();

  std::optional<GpsTimeFix> TryMatchPpsGps(
      uint32_t pps_capture, TickType_t pps_ostime, TickType_t gps_ostime, const ParsedNmea& nmea);

  static void AdjustSystemTime(const GpsTimeFix& time_fix, const CaptureChannel& sw_capture);
};
