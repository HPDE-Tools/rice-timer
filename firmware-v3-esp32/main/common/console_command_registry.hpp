// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <vector>

#include "esp_console.h"

class ConsoleCommandRegistry {
 public:
  static ConsoleCommandRegistry* GetInstance();

  void AddCommand(const esp_console_cmd_t& command);
  esp_err_t Register();

 private:
  std::vector<esp_console_cmd_t> commands_;

  ConsoleCommandRegistry();
};
