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

extern std::string g_device_dir;
extern std::unique_ptr<io::Logger> g_logger;

esp_err_t SetupLogger();

inline esp_err_t SendToLogger(std::string_view line, TickType_t timeout = portMAX_DELAY) {
  return g_logger->AppendLine(line, timeout);
}

inline esp_err_t SendToLoggerFromIsr(std::string_view line) {
  return g_logger->AppendLineFromIsr(line);
}

}  // namespace app
