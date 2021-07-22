// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/controller.hpp"

#include <optional>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "common/macros.hpp"
#include "common/times.hpp"
#include "priorities.hpp"
#include "ui/display.hpp"
#include "ui/encoder_button_input.hpp"
#include "ui/model.hpp"
#include "ui/style.hpp"
#include "ui/view/root.hpp"

namespace ui {

namespace {

constexpr char TAG[] = "ui/controller";
constexpr int kRefreshPeriodMs = 50;

constexpr int kControllerStackSize = 8000;

esp_err_t SetupDisplayDriver() {
  lv_init();
  if constexpr (CONFIG_HW_VERSION == 3) {
    TRY(SetupOled());
    TRY(g_oled->RegisterLvglDriver());
    TRY(g_oled->SetDisplayEnabled(true));
    TRY(RegisterLvglInputDrivers());
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }
  return ESP_OK;
}

}  // namespace

std::unique_ptr<Controller> g_controller{};

esp_err_t SetupUi() {
  g_controller = Controller::Create();
  return g_controller ? ESP_OK : ESP_FAIL;
}

esp_err_t StartUi() {
  if (!g_controller) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_controller->Start();
}

Controller::Controller() = default;
Controller::~Controller() = default;

esp_err_t Controller::Setup() {
  TRY(SetupDisplayDriver());
  TRY(SetupStyle());
  root_ = std::make_unique<view::Root>(lv_scr_act());
  return root_ ? ESP_OK : ESP_FAIL;
}

esp_err_t Controller::Start() { return Task::SpawnSame(TAG, kControllerStackSize, kPriorityUi); }

void Controller::Stop() { Task::Kill(); }

void Controller::Run() {
  static TickType_t last_wake_time = xTaskGetTickCount();

  while (true) {
    const TimeUnixWithUs render_begin_time = NowUnixWithUs();
    root_->Render(g_model);
    const TimeUnixWithUs lv_begin_time = NowUnixWithUs();
    lv_task_handler();
    const TimeUnixWithUs end_time = NowUnixWithUs();
    ESP_LOGD(
        TAG,
        "%lld (render) + %lld (lv) = %lld (total)",
        lv_begin_time - render_begin_time,
        end_time - lv_begin_time,
        end_time - render_begin_time);
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(kRefreshPeriodMs));
  }
}

}  // namespace ui
