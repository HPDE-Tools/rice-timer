// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/view.hpp"

#include <optional>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "app/encoder_button_input.hpp"
#include "app/oled_instance.hpp"
#include "common/logging.hpp"
#include "common/times.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"
#include "ui/style.hpp"
#include "ui/view/root.hpp"

namespace ui {

namespace {

constexpr char TAG[] = "ui/view";
constexpr int kRefreshPeriodMs = 50;

constexpr int kViewStackSize = 8000;

esp_err_t SetupDisplayDriver() {
  lv_init();
  if constexpr (CONFIG_HW_VERSION == 3) {
    TRY(app::SetupOled());
    TRY(app::g_oled->RegisterLvglDriver());
    TRY(app::g_oled->SetDisplayEnabled(true));
    TRY(app::RegisterLvglInputDrivers());
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }
  return ESP_OK;
}

}  // namespace

std::unique_ptr<View> g_view{};

esp_err_t SetupView() {
  g_view = View::Create();
  return g_view ? ESP_OK : ESP_FAIL;
}

View::View() = default;
View::~View() = default;

esp_err_t View::Setup() {
  TRY(SetupDisplayDriver());
  TRY(SetupStyle());
  root_ = std::make_unique<view::Root>(lv_scr_act());
  return root_ ? ESP_OK : ESP_FAIL;
}

esp_err_t View::Start() {
  TRY(Task::SpawnSame(TAG, kViewStackSize, kPriorityUi));
  return ESP_OK;
}

void View::Stop() { Task::Kill(); }

void View::Run() {
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
