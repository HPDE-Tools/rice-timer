// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "io/uart_line_reader.hpp"

#include "common/logging.hpp"
#include "common/scope_guard.hpp"

namespace io {

namespace {
constexpr char TAG[] = "readline";
constexpr int kStackSize = 3000;
}  // namespace

std::unique_ptr<UartLineReader> UartLineReader::Create(
    uart_port_t uart_num, QueueHandle_t queue, Option option) {
  // `new` because private ctor
  auto self = std::unique_ptr<UartLineReader>(new UartLineReader(uart_num, queue, option));
  OK_OR_RETURN(self->Setup(), nullptr);
  return self;
}

UartLineReader::UartLineReader(uart_port_t uart_num, QueueHandle_t queue, Option option)
    : uart_num_(uart_num), queue_(queue), option_(option) {
  CHECK(queue != nullptr);
}

esp_err_t UartLineReader::Setup() {
  ESP_LOGD(TAG, "Setup");
  TRY(uart_enable_pattern_det_baud_intr(
      uart_num_,
      option_.delimiter,
      option_.repeat,
      option_.max_repeat_interval_bits,
      option_.min_post_idle_bits,
      option_.min_pre_idle_bits));
  // undo the enabling if any of the following fails
  MAKE_DEFER(guard_enable) { uart_disable_pattern_det_intr(uart_num_); };
  DiscardInputBuffer();
  // successful; no need to undo
  guard_enable.dismiss();
  active_ = true;
  return ESP_OK;
}

void UartLineReader::Teardown() {
  ESP_LOGD(TAG, "Teardown");
  StopReadLinesAsync();
  DiscardInputBuffer();
  uart_disable_pattern_det_intr(uart_num_);
  active_ = false;
}

esp_err_t UartLineReader::DiscardInputBuffer() {
  TRY(uart_pattern_queue_reset(uart_num_, option_.queue_size));
  TRY(uart_flush_input(uart_num_));
  return ESP_OK;
}

std::string UartLineReader::TryReadOneLine(TickType_t read_timeout) {
  // NOTE(summivox): always `return line` to ensure NRVO (google it!)
  std::string line{};
  if (!active_) {
    ESP_LOGE(TAG, "instance not active");
    return line;  // empty
  }
  const int pos = uart_pattern_pop_pos(uart_num_);
  if (pos < 0) {
    return line;  // empty
  }
  const int len = pos + option_.repeat;
  if (len > option_.max_line_size_bytes) {
    ESP_LOGW(TAG, "line is too long (%d > %d bytes)", len, option_.max_line_size_bytes);
    DiscardInputBuffer();
    return line;  // empty
  }
  line.resize(len);
  const int read_len =
      uart_read_bytes(uart_num_, reinterpret_cast<uint8_t*>(line.data()), len, read_timeout);
  if (read_len != len) {
    ESP_LOGE(TAG, "read bytes error: %d", read_len);
    line.clear();
  }
  return line;
}

std::string UartLineReader::ReadOneLine(TickType_t wait_timeout, TickType_t read_timeout) {
  if (!active_) {
    ESP_LOGE(TAG, "instance not active");
    return {};
  }
  TickType_t start_time_tick = xTaskGetTickCount();
  while (static_cast<int>(xTaskGetTickCount() - start_time_tick) <= wait_timeout) {
    if (std::string line = TryReadOneLine(read_timeout); !line.empty()) {
      return line;
    }
    uart_event_t event;
    if (xQueueReceive(queue_, &event, option_.poll_interval) != pdTRUE) {
      continue;
    }
    switch (event.type) {
      case UART_DATA:
      case UART_PATTERN_DET: {
        continue;
      }
      case UART_FIFO_OVF:
      case UART_BUFFER_FULL: {
        ESP_LOGE(TAG, "uart buffer full; will clear input");
        DiscardInputBuffer();
        return {};
      }
      default: {
        ESP_LOGW(TAG, "unhandled uart event %d", event.type);
        // TODO(summivox): pass through all other events through some mechanism
        return {};
      }
    }
  }  // while not timeout
  return {};
}

esp_err_t UartLineReader::ReadLinesAsync(uint32_t priority, uint32_t cpu, Callback callback) {
  if (!active_) {
    return ESP_ERR_INVALID_STATE;
  }
  CHECK(callback);
  callback_ = callback;
  return Task::SpawnPinned(TAG, kStackSize, priority, cpu);
}

void UartLineReader::StopReadLinesAsync() {
  Task::Kill();
  callback_ = nullptr;
}

void UartLineReader::Run() {
  while (true) {
    std::string line = ReadOneLine();
    if (!line.empty()) {
      if (Callback callback = callback_) {
        callback(std::move(line));
      } else {
        StopReadLinesAsync();
      }
    }
  }
}

}  // namespace io
