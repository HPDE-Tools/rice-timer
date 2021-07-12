// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "freertos/FreeRTOS.h"

class IsrYielder {
 public:
  using BaseTypePtr = BaseType_t*;
  ~IsrYielder() {
    if (should_yield_ == pdTRUE) {
      portYIELD_FROM_ISR();
    }
  }

  operator BaseTypePtr() { return &should_yield_; }

 private:
  BaseType_t should_yield_ = pdFALSE;
};
