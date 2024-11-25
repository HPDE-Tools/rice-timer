// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "common/console_command_registry.hpp"

#include "esp_console.h"

#include "common/macros.hpp"

namespace {
constexpr char TAG[] = "cmd_reg";
}  // namespace

ConsoleCommandRegistry::ConsoleCommandRegistry() {}

ConsoleCommandRegistry* ConsoleCommandRegistry::GetInstance() {
  static ConsoleCommandRegistry* instance = new ConsoleCommandRegistry();
  return instance;
}

void ConsoleCommandRegistry::AddCommand(const esp_console_cmd_t& command) {
  commands_.push_back(command);
}

esp_err_t ConsoleCommandRegistry::Register() {
  esp_err_t first_failure = ESP_OK;
  for (const esp_console_cmd_t& command : commands_) {
    ESP_LOGI(TAG, "registering command: %s", command.command);
    if (const esp_err_t err = esp_console_cmd_register(&command); err != ESP_OK) {
      ESP_LOGE(TAG, "failed to register command (%s): %s", esp_err_to_name(err), command.command);
      first_failure = err;
      // do not fail fast --- see if other commands can be registered or no
    }
  }
  return first_failure;
}
