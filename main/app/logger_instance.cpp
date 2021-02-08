// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/logger_instance.hpp"

#include "app/device_id.hpp"

namespace app {

std::string g_device_dir;
std::unique_ptr<io::Logger> g_logger;

esp_err_t SetupLogger() {
  g_device_dir = fmt::format(
      CONFIG_MOUNT_ROOT "/{:02X}{:02X}{:02X}{:02X}",
      g_device_mac[2],
      g_device_mac[3],
      g_device_mac[4],
      g_device_mac[5]);
  g_logger = std::make_unique<io::Logger>(g_device_dir, io::Logger::Option{});
  return g_logger ? ESP_OK : ESP_FAIL;
}

}  // namespace app
