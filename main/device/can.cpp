// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/can.hpp"

#include <charconv>
#include <string_view>

#include "driver/twai.h"
#include "esp_log.h"
#include "fmt/core.h"
#include "fmt/format.h"

#include "app/logger_instance.hpp"
#include "common/logging.hpp"
#include "common/utils.hpp"
#include "device/capture_manager.hpp"

namespace {

constexpr char TAG[] = "can";

constexpr int kCanStackSize = 6000;

}  // namespace

CanManager::CanManager(Option option) : option_(option) {}
esp_err_t CanManager::Setup() {
  twai_general_config_t general_config =
      TWAI_GENERAL_CONFIG_DEFAULT(option_.tx_pin, option_.rx_pin, option_.mode);
#if CONFIG_TWAI_ISR_IN_IRAM
  general_config.intr_flags = ESP_INTR_FLAG_IRAM;
#endif
  general_config.tx_queue_len = option_.tx_queue_len;
  general_config.rx_queue_len = option_.rx_queue_len;
  twai_filter_config_t filter_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  TRY(twai_driver_install(&general_config, &option_.timing, &filter_config));
  return ESP_OK;
}
CanManager::~CanManager() { Stop(); }

esp_err_t CanManager::Start(CanMessageSubscriber subscriber) {
  subscriber_ = subscriber;
  TRY(twai_start());
  return Task::SpawnSame(TAG, kCanStackSize, option_.priority);
}

void CanManager::Stop() {
  Task::Kill();
  subscriber_ = nullptr;
  twai_stop();
}

void CanManager::Run() {
  while (true) {
    twai_message_t message;
    CHECK_OK(twai_receive(&message, portMAX_DELAY));
    const uint32_t current_capture =
        CaptureManager::GetInstance(MCPWM_UNIT_0)->TriggerNow(MCPWM_SELECT_CAP2);
    if (subscriber_) {
      subscriber_(current_capture, message);
    }
  }
}
