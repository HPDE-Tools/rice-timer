#pragma once

#include <array>
#include <functional>

#include "driver/mcpwm.h"
#include "freertos/FreeRTOS.h"
#include "soc/mcpwm_periph.h"

class CaptureManager;
class CaptureChannel;

class CaptureManager {
 public:
  using Callback = std::function<void(
      mcpwm_unit_t unit, mcpwm_capture_signal_t signal, uint32_t edge, uint32_t value)>;

  static CaptureManager* GetInstance(mcpwm_unit_t unit);
  esp_err_t Enable();
  esp_err_t Disable();
  esp_err_t Subscribe(
      mcpwm_capture_signal_t signal,
      mcpwm_capture_on_edge_t edge,
      uint32_t prescaler,
      Callback callback);
  void Unsubscribe(mcpwm_capture_signal_t signal);
  uint32_t TriggerNow(mcpwm_capture_signal_t signal);
  static uint32_t GetNominalFreqHz();

  CaptureChannel GetChannel(mcpwm_capture_signal_t signal);

  mcpwm_unit_t unit() const { return unit_; }
  mcpwm_dev_t* dev() const { return dev_; }

 private:
  mcpwm_unit_t unit_;
  mcpwm_dev_t* dev_;
  intr_handle_t interrupt_handle_;
  spinlock_t lock_;
  std::array<Callback, 3> callbacks_ = {};

  CaptureManager(mcpwm_unit_t unit, mcpwm_dev_t* dev);
  static void InterruptHandler(CaptureManager* self);
};

class CaptureChannel {
 public:
  CaptureChannel(CaptureManager* manager, mcpwm_capture_signal_t signal)
      : manager_(manager), signal_(signal) {}
  CaptureChannel(mcpwm_unit_t unit, mcpwm_capture_signal_t signal)
      : manager_(CaptureManager::GetInstance(unit)), signal_(signal) {}

  // NOTE(summivox): member functions are `const` because none of _our_ fields are changed,
  // even though `manager_` is internally mutable.

  esp_err_t Subscribe(
      mcpwm_capture_on_edge_t edge, uint32_t prescaler, CaptureManager::Callback callback) const {
    return manager_->Subscribe(signal_, edge, prescaler, callback);
  }
  void Unsubscribe() const { manager_->Unsubscribe(signal_); }
  uint32_t TriggerNow() const { return manager_->TriggerNow(signal_); }
  static uint32_t GetNominalFreqHz() { return CaptureManager::GetNominalFreqHz(); }

  mcpwm_unit_t unit() const { return manager_->unit(); }
  mcpwm_dev_t* dev() const { return manager_->dev(); }
  mcpwm_capture_signal_t signal() const { return signal_; }

 private:
  CaptureManager* manager_;
  mcpwm_capture_signal_t signal_;
};
