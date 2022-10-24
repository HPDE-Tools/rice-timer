// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "fmt/core.h"
#include "freertos/FreeRTOS.h"

#include "io/logger.hpp"

namespace app {

enum ProducerId {
  kGpsProducer,
  kImuProducer,
  kCanProducer,
  kHeartbeatProducer,
  kNumProducers,
};

extern std::string g_device_dir;
extern std::unique_ptr<io::Logger> g_logger;

esp_err_t SetupAndStartLoggerTask();
esp_err_t StartNewLoggingSession();
esp_err_t StopLogging();

inline esp_err_t SendToLogger(ProducerId producer_id, std::string_view line) {
  if (!g_logger) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_logger->AppendLine((int)producer_id, line);
}

}  // namespace app
