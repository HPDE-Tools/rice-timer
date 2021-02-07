// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "device/capture_manager.hpp"

#include "esp32/clk.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"

#include "common/logging.hpp"
#include "common/scope_guard.hpp"

CaptureManager::CaptureManager(mcpwm_unit_t unit, mcpwm_dev_t* dev) : unit_(unit), dev_(dev) {
  mcpwm_isr_register(
      unit_,
      reinterpret_cast<intr_handler_t>(&InterruptHandler),
      this,
      /*flag*/ 0,
      &interrupt_handle_);
  vPortCPUInitializeMutex(&lock_);
}

CaptureManager* CaptureManager::GetInstance(mcpwm_unit_t unit) {
  static CaptureManager instances[] = {
      {MCPWM_UNIT_0, &MCPWM0},
      {MCPWM_UNIT_1, &MCPWM1},
  };
  CHECK(0 <= unit && unit < MCPWM_UNIT_MAX);
  return &instances[unit];
}

CaptureChannel CaptureManager::GetChannel(mcpwm_capture_signal_t signal) { return {this, signal}; }

esp_err_t CaptureManager::Enable() { return esp_intr_enable(interrupt_handle_); }

esp_err_t CaptureManager::Disable() { return esp_intr_disable(interrupt_handle_); }

esp_err_t CaptureManager::Subscribe(
    mcpwm_capture_signal_t signal,
    mcpwm_capture_on_edge_t edge,
    uint32_t prescaler,
    Callback callback) {
  CHECK(0 <= signal && signal < 3);
  vPortEnterCritical(&lock_);
  SCOPE_EXIT { vPortExitCritical(&lock_); };
  TRY(mcpwm_capture_enable(unit_, signal, edge, prescaler));
  callbacks_[signal] = callback;
  switch (signal) {
    case MCPWM_SELECT_CAP0:
      dev_->int_ena.cap0_int_ena = true;
      break;
    case MCPWM_SELECT_CAP1:
      dev_->int_ena.cap1_int_ena = true;
      break;
    case MCPWM_SELECT_CAP2:
      dev_->int_ena.cap2_int_ena = true;
      break;
  }
  return ESP_OK;
}

void CaptureManager::Unsubscribe(mcpwm_capture_signal_t signal) {
  CHECK(0 <= signal && signal < 3);
  vPortEnterCritical(&lock_);
  SCOPE_EXIT { vPortExitCritical(&lock_); };
  switch (signal) {
    case MCPWM_SELECT_CAP0:
      dev_->int_ena.cap0_int_ena = false;
      break;
    case MCPWM_SELECT_CAP1:
      dev_->int_ena.cap1_int_ena = false;
      break;
    case MCPWM_SELECT_CAP2:
      dev_->int_ena.cap2_int_ena = false;
      break;
  }
  callbacks_[signal] = nullptr;
  mcpwm_capture_disable(unit_, signal);
}

uint32_t CaptureManager::TriggerNow(mcpwm_capture_signal_t signal) {
  vPortEnterCritical(&lock_);
  SCOPE_EXIT { vPortExitCritical(&lock_); };
  dev_->cap_cfg_ch[signal].en = true;
  dev_->cap_cfg_ch[signal].sw = true;
  return dev_->cap_val_ch[signal];
}

uint32_t CaptureManager::GetNominalFreqHz() { return esp_clk_apb_freq(); }

void CaptureManager::InterruptHandler(CaptureManager* self) {
  if (self->dev_->int_st.cap0_int_st) {
    self->dev_->int_clr.cap0_int_clr = true;
    const uint32_t edge = self->dev_->cap_status.cap0_edge;
    const uint32_t value = self->dev_->cap_val_ch[0];
    if (auto& callback = self->callbacks_[0]) {
      callback(self->unit_, MCPWM_SELECT_CAP0, edge, value);
    }
  }
  if (self->dev_->int_st.cap1_int_st) {
    self->dev_->int_clr.cap1_int_clr = true;
    const uint32_t edge = self->dev_->cap_status.cap1_edge;
    const uint32_t value = self->dev_->cap_val_ch[1];
    if (auto& callback = self->callbacks_[1]) {
      callback(self->unit_, MCPWM_SELECT_CAP1, edge, value);
    }
  }
  if (self->dev_->int_st.cap2_int_st) {
    self->dev_->int_clr.cap2_int_clr = true;
    const uint32_t edge = self->dev_->cap_status.cap2_edge;
    const uint32_t value = self->dev_->cap_val_ch[2];
    if (auto& callback = self->callbacks_[2]) {
      callback(self->unit_, MCPWM_SELECT_CAP2, edge, value);
    }
  }
}
