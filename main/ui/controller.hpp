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

struct Screen;

struct IdleScreen;
struct DebugScreen;
struct TrackReqScreen;
struct TrackSelScreen;
struct TrackTimerScreen;

}  // namespace view

class Controller : public Task {
 public:
  ~Controller() override;

  esp_err_t Start();
  void Stop();

  DEFINE_CREATE(Controller)

 protected:
  void Run() override;

 private:
  std::unique_ptr<view::IdleScreen> idle_screen_;
  std::unique_ptr<view::DebugScreen> debug_screen_;
  std::unique_ptr<view::TrackReqScreen> track_req_screen_;
  std::unique_ptr<view::TrackSelScreen> track_sel_screen_;
  std::unique_ptr<view::TrackTimerScreen> track_timer_screen_;

  view::Screen* loaded_screen_;  // not owned

  Controller();
  esp_err_t Setup();

  bool IsOnTrack() const;
  void TryStartLogger();
  void StopLogger();
};

extern std::unique_ptr<Controller> g_controller;

esp_err_t SetupUi();
esp_err_t StartUi();

}  // namespace ui
