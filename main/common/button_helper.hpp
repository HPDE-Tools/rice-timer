// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "common/utils.hpp"

class ButtonHelper {
 public:
  enum Result {
    kReleased,       // is not pressed
    kPressed,        // first got pressed
    kShortHold,      // has been held for less than long_duration
    kLongHold,       // has been held for at least long_duration
    kLongHoldBegin,  // first time entering long-hold state
    kShortClick,     // released after held for less than long_duration
    kLongClick,      // released after held for at least long_duration
  };

  ButtonHelper(int long_duration) : long_duration_(long_duration) { Reset(); }

  void Reset() {
    last_press_time_ = xTaskGetTickCount();
    last_state_ = false;
    is_long_ = false;
  }

  Result Update(bool curr_state) {
    const TickType_t now = xTaskGetTickCount();
    const auto dt = SignedMinus(now, last_press_time_);
    Result result = kReleased;
    if (last_state_) {
      const bool curr_is_long = is_long_ || dt >= long_duration_;
      const bool first_long = !is_long_ && curr_is_long;
      is_long_ = curr_is_long;
      if (curr_state) {
        // H -> H
        result = first_long ? kLongHoldBegin : is_long_ ? kLongHold : kShortHold;
      } else {
        // H -> L (falling edge)
        result = is_long_ ? kLongClick : kShortClick;
        Reset();
      }
    } else {
      if (curr_state) {
        // L -> H (rising edge)
        last_press_time_ = now;
        result = kPressed;
      } else {
        // L -> L
        result = kReleased;
      }
    }
    last_state_ = curr_state;
    return result;
  }

  int GetHoldTime() {
    return last_state_ ? SignedMinus(xTaskGetTickCount(), last_press_time_) : -1;
  }

 private:
  int long_duration_;

  TickType_t last_press_time_{};
  bool last_state_ = false;
  bool is_long_ = false;
};
