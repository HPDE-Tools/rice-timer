#pragma once

#include <time.h>
#include <atomic>
#include <memory>
#include <string_view>

#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "driver/uart.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/uart_struct.h"

#include "capture_manager.hpp"
#include "common/macros.hpp"
#include "common/task.hpp"
#include "io/uart_line_reader.hpp"

class GpsManager : public Task {
 public:
  struct Option {
    uart_port_t uart_num = -1;
    uart_dev_t* uart_dev = nullptr;
    gpio_num_t uart_rx_pin = GPIO_NUM_NC;
    gpio_num_t uart_tx_pin = GPIO_NUM_NC;

    mcpwm_unit_t pps_capture_unit = MCPWM_UNIT_0;
    mcpwm_capture_signal_t pps_capture_signal = MCPWM_SELECT_CAP0;
    mcpwm_io_signals_t pps_capture_io = MCPWM_CAP_0;
    gpio_num_t pps_pin = GPIO_NUM_NC;
    mcpwm_capture_signal_t software_capture_signal = MCPWM_SELECT_CAP2;

    bool adjust_system_time;

    int priority = 0;
  };

  struct PpsGpsMatch {
    TickType_t pps_time_os;
    uint32_t pps_time_capture;
    TickType_t gps_time_os;
    uint32_t gps_time_capture;
    tm gps_nmea_tm;
    time_t gps_nmea_unix;
  };

  static std::unique_ptr<GpsManager> Create(Option option) {
    auto self = std::unique_ptr<GpsManager>(new GpsManager(option));
    if (self->Setup() != ESP_OK) {
      self.reset();
    }
    return self;
  }

  virtual ~GpsManager();

  esp_err_t Start();
  void Stop();

  /// Sends arbitrary content over UART
  ///
  /// \param payload content to write to UART
  /// \returns ESP_FAIL if failed to write to UART;
  ///          ESP_OK otherwise.
  esp_err_t SendRaw(std::string_view raw);

  /// Sends an NMEA sentence, automatically prepending and appending framing and checksum.
  ///
  /// \param payload NMEA sentence between '$' and '*' (excluding both delimiters)
  /// \returns ESP_FAIL if failed to write to UART;
  ///          ESP_OK otherwise.
  ///
  /// \example payload: "GPRMC,whatever,123,456,test"
  ///          actually sent to UART: "$GPRMC,whatever,123,456,test*54\r\n"
  esp_err_t SendNmea(std::string_view payload);

  /// Reads one LF-delimited line from UART (blocking)
  std::string ReadRawLine(TickType_t timeout);

  /// Have we received a PPS recently?
  /// This will actively check and update the last known state if PPS has recently became stale.
  ///
  /// \see is_pps_recent -- returns last known state only
  bool CheckIsPpsRecent();

  uart_port_t uart_num() const { return option_.uart_num; }
  uart_dev_t* uart_dev() const { return option_.uart_dev; }
  QueueHandle_t uart_queue() const { return uart_queue_; }
  bool is_pps_recent() const { return is_pps_recent_; }

  // NOTE(summivox): returns a copy to avoid surprise changes
  PpsGpsMatch latest_pps_gps_match() const { return latest_pps_gps_match_; }

 protected:
  void Run() override;

 private:
  Option option_;
  QueueHandle_t uart_queue_;
  std::unique_ptr<io::UartLineReader> line_reader_;
  CaptureManager* capture_manager_ = nullptr;  // not owned

  // GPRMC provides only 2-digit year (other sources might provide this)
  int century_ = 2000;

  volatile TickType_t latest_pps_time_os_ = 0;     // written from ISR
  volatile uint32_t latest_pps_time_capture_ = 0;  // written from ISR

  // PPS freshness:
  // - set to true only by ISR
  // - set to false only by CheckIsPpsRecent
  std::atomic_bool is_pps_recent_ = false;

  PpsGpsMatch latest_pps_gps_match_{};

  explicit GpsManager(Option option);
  esp_err_t Setup();

  // called by CaptureManager ISR
  static void HandlePpsCapture(
      GpsManager* self,
      mcpwm_unit_t unit,
      mcpwm_capture_signal_t signal,
      uint32_t edge,
      uint32_t value);
  void ProcessGpsLine(std::string_view trimmed_line, TickType_t time_os, uint32_t time_capture);
  void AdjustSystemTime(const PpsGpsMatch& match);

  NON_COPYABLE_NOR_MOVABLE(GpsManager)
};

esp_err_t MtkDetectAndConfigure(GpsManager* gps, int baud_rate, int output_period_ms);
