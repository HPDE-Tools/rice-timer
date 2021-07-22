// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common/macros.hpp"
#include "common/task.hpp"

namespace ui {

namespace view {
struct Root;
}

class Controller : public Task {
 public:
  ~Controller() override;

  esp_err_t Start();
  void Stop();

  DEFINE_CREATE(Controller)

 protected:
  void Run() override;

 private:
  std::unique_ptr<view::Root> root_;

  Controller();
  esp_err_t Setup();
};

extern std::unique_ptr<Controller> g_controller;

esp_err_t SetupUi();
esp_err_t StartUi();

}  // namespace ui
