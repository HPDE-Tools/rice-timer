// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "ui/controller.hpp"

#include <optional>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

#include "app/logger_instance.hpp"
#include "common/button_helper.hpp"
#include "common/macros.hpp"
#include "common/perf.hpp"
#include "common/times.hpp"
#include "priorities.hpp"
#include "ui/display.hpp"
#include "ui/encoder_button_input.hpp"
#include "ui/model.hpp"
#include "ui/style.hpp"
// #include "ui/view/debug_screen.hpp"
#include "ui/view/idle_screen.hpp"
// #include "ui/view/softkey_prompt.hpp"
// #include "ui/view/track_req_screen.hpp"
// #include "ui/view/track_sel_screen.hpp"
#include "ui/view/track_timer_screen.hpp"

DEFINE_PERF(ui_controller);

namespace ui {

namespace {

constexpr char TAG[] = "ui/controller";
constexpr int kRefreshPeriodMs = 50;
constexpr int kLongPressDurationMs = 1500;

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

void SetFlipped(bool flipped) {
  g_oled->SetFlipLr(flipped);
  g_oled->SetFlipUd(flipped);
  g_encoder_dir = flipped ? -1 : +1;
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
  // debug_screen_ = std::make_unique<view::DebugScreen>();
  // track_req_screen_ = std::make_unique<view::TrackReqScreen>();
  // track_sel_screen_ = std::make_unique<view::TrackSelScreen>();
  track_timer_screen_ = std::make_unique<view::TrackTimerScreen>();

  // softkey_prompt_1_ = std::make_unique<view::SoftkeyPrompt>();
  // softkey_prompt_3_ = std::make_unique<view::SoftkeyPrompt>();

  SetFlipped(flipped_);

  return ESP_OK;
}

esp_err_t Controller::Start() { return Task::SpawnSame(TAG, kControllerStackSize, kPriorityUi); }

void Controller::Stop() { Task::Kill(); }

void Controller::Run() {
  TickType_t last_wake_time = xTaskGetTickCount();

  ButtonHelper button1_helper(pdMS_TO_TICKS(kLongPressDurationMs));
  ButtonHelper button3_helper(pdMS_TO_TICKS(kLongPressDurationMs));

  idle_screen_->Render(g_model);
  loaded_screen_ = idle_screen_->Load();

  idle_screen_->btn_settings_click = [this](lv_event_t* e) {
    ESP_LOGI(TAG, "loading debug");
    // loaded_screen_ = debug_screen_->Load();
  };
  idle_screen_->btn_track_click = [this](lv_event_t* e) {
    ESP_LOGI(TAG, "loading track req");
    loaded_screen_ = track_timer_screen_->Load();  // hack: skip the lobby
  };
  idle_screen_->btn_flip_click = [this](lv_event_t* e) {
    flipped_ = !flipped_;
    SetFlipped(flipped_);
    ESP_LOGI(TAG, "flipping screen: %d", (int)flipped_);
  };
  // track_req_screen_->on_success = [this](lv_event_t* e) {
  //   ESP_LOGI(TAG, "loading track sel");
  //   loaded_screen_ = track_sel_screen_->LoadAnim(
  //       LV_SCR_LOAD_ANIM_OVER_TOP, /*anim time*/ 500, /*delay*/ 1000, false);
  // };

  while (true) {
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(kRefreshPeriodMs));
    SCOPE_PERF(ui_controller);

    // HACK: buttons 1 and 3 are also flipped; not sure where is the best place to put this
    const ButtonHelper::Result button1 = button1_helper.Update(GetButtonState(flipped_ ? 3 : 1));
    const ButtonHelper::Result button3 = button3_helper.Update(GetButtonState(flipped_ ? 1 : 3));
    switch (button1) {
      case ButtonHelper::kShortClick: {
        TryStartLogger();
        break;
      }
      case ButtonHelper::kLongHoldBegin: {
        StopLogger();
        break;
      }
      default:
        break;
    }
    switch (button3) {
      case ButtonHelper::kShortClick: {
        if (IsOnTrack()) {
          break;
        }
        [[fallthrough]];
      }
      case ButtonHelper::kLongHoldBegin: {
        loaded_screen_ = idle_screen_->Load();
        break;
      }
      case ButtonHelper::kShortHold: {
        // ESP_LOGI(TAG, "btn3 hold=%d", button3_helper.GetHoldTime());
        break;
      }
      default:
        break;
    }

    loaded_screen_->Render(g_model);
    lv_task_handler();
  }
}

bool Controller::IsOnTrack() const {
  return loaded_screen_ && loaded_screen_ == track_timer_screen_.get();
}

void Controller::TryStartLogger() {
  if (!g_model.sd_card) {
    ESP_LOGW(TAG, "cannot start logger: no sd card");
    // TODO: report no SD card to UI
    return;
  }
  if (const esp_err_t err = app::StartNewLoggingSession(); err != ESP_OK) {
    ESP_LOGE(TAG, "cannot start logger: %s", esp_err_to_name(err));
    // TODO: report error to UI
    return;
  }
  ESP_LOGI(TAG, "sent logger start request");
  // TODO: report success to UI
}

void Controller::StopLogger() {
  app::StopLogging();
  ESP_LOGI(TAG, "sent logger stop request");
}

}  // namespace ui
