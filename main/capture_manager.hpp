#pragma once

#include <array>

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

class CaptureManager {
 public:
  using Callback = void (*)(CaptureManager* capture_manager,
                            mcpwm_capture_signal_t signal,
                            uint32_t edge,
                            uint32_t value);

  static CaptureManager* GetInstance(mcpwm_unit_t unit);
  esp_err_t Enable();
  esp_err_t Disable();
  esp_err_t Subscribe(mcpwm_capture_signal_t signal,
                      mcpwm_capture_on_edge_t edge,
                      uint32_t prescaler,
                      Callback callback);
  esp_err_t Unsubscribe(mcpwm_capture_signal_t signal);
  uint32_t TriggerNow(mcpwm_capture_signal_t signal);
  static uint32_t GetNominalFreqHz();

  mcpwm_unit_t unit() const { return unit_; }
  mcpwm_dev_t* dev() const { return dev_; }

 private:
  mcpwm_unit_t unit_;
  mcpwm_dev_t* dev_;
  intr_handle_t interrupt_handle_;
  std::array<Callback, 3> callbacks_ = {};

  CaptureManager(mcpwm_unit_t unit, mcpwm_dev_t* dev);
  static void IRAM_ATTR InterruptHandler(CaptureManager* self);
};
