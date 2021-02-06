#pragma once

#include <atomic>
#include <functional>
#include <memory>

#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "common/task.hpp"

namespace io {

class UartLineReader : public ::Task {
 public:
  using Callback = std::function<void(std::string&& line_with_delimiter)>;

  struct Option {
    /// each "line" is delimited by `delimiter` repeated `repeat` times.
    /// \example delimiter = '*', repeat = 3 means "***" will be used as line separator
    char delimiter = '\n';
    /// each "line" is delimited by `delimiter` repeated `repeat` times.
    /// \example delimiter = '*', repeat = 3 means "***" will be used as line separator
    int repeat = 1;

    /// at most return this many bytes per "line"; longer lines will be discarded
    int max_line_size_bytes = 256;

    /// max idle time allowed between two adjacent delimiter chars (unit: UART baud clock ticks)
    int max_repeat_interval_bits = 9;
    /// min idle time required after the delimiter chars (unit: UART baud clock ticks)
    int min_post_idle_bits = 0;
    /// min idle time required before the delimiter chars (unit: UART baud clock ticks)
    int min_pre_idle_bits = 0;

    /// line notification queue size (in UART driver)
    int queue_size = 16;
    /// how often the line notification queue is checked
    TickType_t poll_interval = 1;
  };

  /// Creates a line reader on a UART with initialized driver and event queue.
  /// Note that no lines are read until one of the Read methods is called.
  ///
  /// \param uart_num UART from which lines are read
  /// \param queue initialized event queue from `uart_driver_install`
  /// \param option
  static std::unique_ptr<UartLineReader> Create(
      uart_port_t uart_num, QueueHandle_t queue, Option option);

  virtual ~UartLineReader() { Teardown(); }

  /// \returns whether this instance is still alive (not killed due to faults)
  bool active() const { return active_; }

  esp_err_t DiscardInputBuffer();

  /// Read one line (including delimiter chars) only if there is already a buffered line available.
  ///
  /// \param read_timeout timeout for the UART read bytes operation (default = 0; non-blocking)
  /// \returns empty string if there is no line to be read;
  ///          otherwise non-empty line (including delimiter chars)
  std::string TryReadOneLine(TickType_t read_timeout = 0);

  /// Read one line (including delimiter chars), blocking the current thread until one is available
  /// or timeout.
  ///
  /// \param wait_timeout timeout for the whole operation (default = forever)
  /// \param read_timeout timeout for the UART read bytes operation (default = forever)
  /// \returns empty string when timeout / error;
  ///          otherwise non-empty line (including delimiter chars)
  std::string ReadOneLine(
      TickType_t wait_timeout = portMAX_DELAY, TickType_t read_timeout = portMAX_DELAY);

  /// Starts a background task that reads every line (including delimiter chars) as it comes.
  /// This task will share the same CPU as caller.
  ///
  /// \param priority priority for the reader background task
  /// \param callback will be called each time a line is read with line (including delimiter chars)
  /// \returns
  esp_err_t ReadLinesAsync(uint32_t priority, Callback callback) {
    return ReadLinesAsync(priority, xPortGetCoreID(), callback);
  }

  /// Starts a background task that reads every line (including delimiter chars) as it comes.
  /// This task will be pinned to the specified CPU.
  ///
  /// \param priority priority for the reader background task
  /// \param cpu cpu to which the reader background task is pinned
  /// \param callback will be called each time a line is read with line (including delimiter chars)
  esp_err_t ReadLinesAsync(uint32_t priority, uint32_t cpu, Callback callback);

  /// Stops the line-reading background task if it is running.
  void StopReadLinesAsync();

 protected:
  void Run() override;

 private:
  bool active_ = false;
  uart_port_t uart_num_;
  QueueHandle_t queue_ = nullptr;
  Option option_;
  Callback callback_ = nullptr;
  TaskHandle_t task_ = nullptr;

  UartLineReader(uart_port_t uart_num, QueueHandle_t queue, Option option);
  esp_err_t Setup();
  void Teardown();
};

}  // namespace io
