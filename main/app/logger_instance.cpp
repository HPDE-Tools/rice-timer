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
}

void HandleLoggerExit(const io::Logger::Error error) {
  ESP_LOGE(TAG, "logger exit: %d", (int)error);
  ui::g_model.logger.reset();
}

}  // namespace

std::string g_device_dir{};
std::unique_ptr<io::Logger> g_logger{};

esp_err_t SetupLogger() {
  g_device_dir = fmt::format(
      CONFIG_MOUNT_ROOT "/{:02X}{:02X}{:02X}{:02X}",
      g_device_mac[2],
      g_device_mac[3],
      g_device_mac[4],
      g_device_mac[5]);
  g_logger = std::make_unique<io::Logger>(
      g_device_dir,
      kNumProducers,
      io::Logger::Option{
          .queue_size_bytes = 90000,
          .write_buffer_size_bytes = 8192,
      });
  return g_logger ? ESP_OK : ESP_FAIL;
}

esp_err_t StartLogger() {
  if (!g_logger) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_logger->Start(NewSessionId(), /*init split id*/ 0, HandleLoggerCommit, HandleLoggerExit);
}

}  // namespace app
