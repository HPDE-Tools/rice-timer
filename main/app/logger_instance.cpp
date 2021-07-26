// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/logger_instance.hpp"

#include "app/device_id.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "app/logger";

void HandleLoggerCommit(const io::Logger& logger, TickType_t now) {
  ui::g_model.logger = ui::Model::Logger{
      .session_id = logger.session_id(),
      .split_id = logger.split_id(),
      .lines = logger.lines_committed(),
  };
  ui::g_model.is_logger_running = true;
}

void HandleLoggerStateChange(io::Logger::State state, io::Logger::Error last_error) {
  ESP_LOGI(TAG, "state=%d last_error=%d", (int)state, (int)last_error);
  switch (state) {
    case io::Logger::kStopped: {
      ui::g_model.logger.reset();
      ui::g_model.is_logger_running = false;
    } break;
    case io::Logger::kRunning: {
      ui::g_model.is_logger_running = true;
    } break;
    default:
      CHECKED_UNREACHABLE;
  }
}

}  // namespace

std::string g_device_dir{};
std::unique_ptr<io::Logger> g_logger{};

esp_err_t SetupAndStartLoggerTask() {
  g_device_dir = fmt::format(
      CONFIG_MOUNT_ROOT "/{:02X}{:02X}{:02X}{:02X}",
      g_device_mac[2],
      g_device_mac[3],
      g_device_mac[4],
      g_device_mac[5]);
  g_logger = std::make_unique<io::Logger>(
      g_device_dir,
      kNumProducers,
      HandleLoggerCommit,
      HandleLoggerStateChange,
      io::Logger::Option{
          .queue_size_bytes = 90000,
          .write_buffer_size_bytes = 8192,
      });
  if (!g_logger) {
    return ESP_FAIL;
  }
  // NOTE: logger host task will start in idle state, blocked almost immediately
  return g_logger->StartTask();
}

esp_err_t StartNewLoggingSession() {
  if (!g_logger) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_logger->StartNewSession();
}

esp_err_t StopLogging() {
  if (!g_logger) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_logger->StopLogging();
}

}  // namespace app
