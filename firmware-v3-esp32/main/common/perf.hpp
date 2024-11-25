// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <string>
#include <string_view>
#include <type_traits>

#include "driver/gpio.h"

#include "common/circular_buffer.hpp"
#include "common/macros.hpp"
#include "common/times.hpp"
#include "common/utils.hpp"
#include "device/capture_manager.hpp"

class PerfCollector {
 public:
  static constexpr int kSampleDepth = 16;  // TODO: customizable

  class Scope final {
   public:
    static constexpr int kUsInCapture = APB_CLK_FREQ / 1'000'000;
    explicit Scope(PerfCollector* host, gpio_num_t pin = GPIO_NUM_NC) : host_(host), pin_(pin) {
      Start();
    }
    ~Scope() { Stop(); }

    void Start() {
      start_ = Now();
      if (pin_ != GPIO_NUM_NC) {
        gpio_set_level(pin_, 1);
      }
      running_ = true;
    }
    void Stop() {
      if (running_) {
        host_->Update(SignedMinus(Now(), start_) / kUsInCapture);
        if (pin_ != GPIO_NUM_NC) {
          gpio_set_level(pin_, 0);
        }
        running_ = false;
      }
    }

   private:
    PerfCollector* host_;
    gpio_num_t pin_ = GPIO_NUM_NC;
    uint32_t start_;
    bool running_ = false;

    static uint32_t Now() {
      return CaptureManager::GetInstance(MCPWM_UNIT_1)->TriggerNow(MCPWM_SELECT_CAP0);
    }
  };

  explicit PerfCollector(std::string_view name) : name_(name), buf_(kSampleDepth) {
    CaptureManager::GetInstance(MCPWM_UNIT_1)
        ->Subscribe(MCPWM_SELECT_CAP0, MCPWM_POS_EDGE, 0, nullptr);
  }

  void Update(int32_t duration_us) {
    ++count_;
    buf_.push_back(duration_us);
  }

  void Dump() const;

 private:
  std::string name_{};
  int32_t count_ = 0;
  CircularBuffer<int32_t> buf_;
};

#define DECLARE_PERF(name)          \
  namespace _perf {                 \
  extern PerfCollector PERF_##name; \
  }                                 \
  using _perf::PERF_##name

#define DEFINE_PERF(name)           \
  namespace _perf {                 \
  PerfCollector PERF_##name{#name}; \
  }                                 \
  using _perf::PERF_##name

#define SCOPE_PERF(name) ::PerfCollector::Scope _scope_##name##_##__COUNTER__(&::_perf::PERF_##name)
