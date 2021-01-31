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

#include "capture_manager.hpp"
#include "common/macros.hpp"
#include "common/perishable.hpp"
#include "common/task.hpp"
#include "device/gps_utils.hpp"
#include "io/uart_line_reader.hpp"

class GpsDaemon : public Task {
 public:
  static constexpr int kBuildCentury = ((__DATE__[7] - '0') * 1000 + (__DATE__[8] - '0') * 100);
  static_assert(kBuildCentury == 2000);  // sure...

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
    kLost,
    kAwaitingNmea,
    kAwaitingTimeFix,
    kActive,
  };

  using GpsSetupHandler = std::function<bool(io::UartLineReader* line_reader)>;
  using GpsRawLineSubscriber = std::function<void(std::string_view line, bool is_valid_nmea)>;
  using GpsDataSubscriber = std::function<void(
      State state, const ParsedNmea& nmea, const std::optional<GpsTimeFix>& time_fix)>;

  static std::unique_ptr<GpsDaemon> Create(
      io::UartLineReader* line_reader,
      CaptureManager* capture_manager,
      GpsSetupHandler setup_handler,
      Option option) {
    std::unique_ptr<GpsDaemon> self(
        new GpsDaemon(line_reader, capture_manager, setup_handler, option));
    if (self->Setup() != ESP_OK) {
      self.reset();
    }
    return self;
  }

  virtual ~GpsDaemon();

  esp_err_t Start(GpsDataSubscriber&& data_subscriber, GpsRawLineSubscriber&& line_subscriber);
  void Stop();

  void PpsCaptureIsr(uint32_t value);

  State state() const { return state_; }
  auto latest_pps() const { return latest_pps_.Get(); }
  auto latest_gps() const { return latest_gps_.Get(); }

  static void AdjustSystemTime(const GpsTimeFix& time_fix, const CaptureChannel& sw_capture);

 protected:
  void Run() override;

 private:
  const Option option_;
  io::UartLineReader* const line_reader_;  // not owned
  CaptureManager* const capture_manager_;  // not owned
  const CaptureChannel sw_capture_;        // derived from capture manager
  GpsSetupHandler setup_;
  GpsDataSubscriber data_subscriber_;
  GpsRawLineSubscriber line_subscriber_;

  std::atomic<State> state_ = kLost;
  Perishable</*data*/ uint32_t, /*time*/ TickType_t> latest_pps_;
  Perishable</*data*/ ParsedNmea, /*time*/ TickType_t> latest_gps_;

  int century_;

  GpsDaemon(
      io::UartLineReader* line_reader,
      CaptureManager* capture_manager,
      GpsSetupHandler setup_handler,
      Option option);

  esp_err_t Setup();
  void ResetLatest();

  std::optional<GpsTimeFix> TryMatchPpsGps(
      uint32_t pps_capture, TickType_t pps_ostime, TickType_t gps_ostime, const ParsedNmea& nmea);
};
