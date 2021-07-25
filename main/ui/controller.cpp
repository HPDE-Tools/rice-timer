// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/controller.hpp"

#include <optional>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "common/button_helper.hpp"
#include "common/macros.hpp"
#include "common/times.hpp"
#include "priorities.hpp"
#include "ui/display.hpp"
#include "ui/encoder_button_input.hpp"
#include "ui/model.hpp"
#include "ui/style.hpp"
#include "ui/view/debug_screen.hpp"
#include "ui/view/idle_screen.hpp"
#include "ui/view/track_req_screen.hpp"
#include "ui/view/track_sel_screen.hpp"

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
  TRY(SetupTheme());
  idle_screen_ = std::make_unique<view::IdleScreen>();
  debug_screen_ = std::make_unique<view::DebugScreen>();
  track_req_screen_ = std::make_unique<view::TrackReqScreen>();
  track_sel_screen_ = std::make_unique<view::TrackSelScreen>();
  return ESP_OK;
}

esp_err_t Controller::Start() { return Task::SpawnSame(TAG, kControllerStackSize, kPriorityUi); }

void Controller::Stop() { Task::Kill(); }

void Controller::Run() {
  TickType_t last_wake_time = xTaskGetTickCount();

  ButtonHelper button3_helper(pdMS_TO_TICKS(1500));

  idle_screen_->Render(g_model);
  loaded_screen_ = idle_screen_->Load();

  idle_screen_->btn_settings_click = [this](lv_event_t* e) {
    ESP_LOGI(TAG, "loading debug");
    loaded_screen_ = debug_screen_->Load();
  };
  idle_screen_->btn_track_click = [this](lv_event_t* e) {
    ESP_LOGI(TAG, "loading track req");
    loaded_screen_ = track_req_screen_->Load();
  };
  track_req_screen_->handle_success = [this](lv_event_t* e) {
    ESP_LOGI(TAG, "loading track sel");
    loaded_screen_ = track_sel_screen_->LoadAnim(
        LV_SCR_LOAD_ANIM_OVER_TOP, /*anim time*/ 500, /*delay*/ 1000, false);
  };

  while (true) {
    const TimeUnixWithUs render_begin_time = NowUnixWithUs();

    gpio_set_level(GPIO_NUM_17, 1);  // DEBUG

    const ButtonHelper::Result button3 = button3_helper.Update(GetButtonState(3));
    switch (button3) {
      case ButtonHelper::kShortClick: {
        ESP_LOGI(TAG, "btn3 short click");
        // TODO: compare with "on-track screen"
        if (loaded_screen_ == nullptr) {
          break;
        }
        [[fallthrough]];
      }
      case ButtonHelper::kLongClick: {
        ESP_LOGI(TAG, "btn3 click");
        loaded_screen_ = idle_screen_->Load();
        break;
      }
      case ButtonHelper::kShortHold: {
        ESP_LOGI(TAG, "btn3 hold=%d", button3_helper.GetHoldTime());
        break;
      }
      default:
        break;
    }

    loaded_screen_->Render(g_model);

    gpio_set_level(GPIO_NUM_17, 0);  // DEBUG

    const TimeUnixWithUs lv_begin_time = NowUnixWithUs();
    gpio_set_level(GPIO_NUM_16, 1);  // DEBUG
    lv_task_handler();
    gpio_set_level(GPIO_NUM_16, 0);  // DEBUG
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
