// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "freertos/FreeRTOS.h"

class IsrYielder {
 public:
  __attribute__((always_inline)) ~IsrYielder() {
    if (should_yield_ == pdTRUE) {
      portYIELD_FROM_ISR();
    }
  }

  __attribute__((always_inline)) operator BaseType_t*() { return &should_yield_; }

 private:
  BaseType_t should_yield_ = pdFALSE;
};
