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

// NOTE: This module is all boilerplate.
// The actual view implementation is hidden through pimpl.

namespace view {
struct Root;
}

class View : public Task {
 public:
  ~View() override;

  esp_err_t Start();
  void Stop();

  DEFINE_CREATE(View)

 protected:
  void Run() override;

 private:
  std::unique_ptr<view::Root> root_;

  View();
  esp_err_t Setup();
};

extern std::unique_ptr<View> g_view;

esp_err_t SetupView();

}  // namespace ui
