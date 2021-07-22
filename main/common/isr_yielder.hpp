// Authors: summivox@gmail.com

#pragma once

#include "freertos/FreeRTOS.h"

/// Helper for simplifying a common pattern when calling FreeRTOS API functions in an interrupt
/// handler, a.k.a. interrupt service routine (ISR).
///
/// Most `...FromISR` functions expect a `BaseType_t *pxHigherPriorityTaskWoken` argument in the
/// last position. Handling this properly is required, but doing so is noisy and tedious in the
/// (usually short) ISR. Instead you may simply declare an `IsrYielder` inside the ISR and pass it
/// as the `pxHigherPriorityTaskWoken` argument; it will automatically clean up as required.
///
/// \example
/// \code{.cpp}
/// SemaphoreHandle_t semaphore;
/// void InterruptHandler() {
///   IsrYielder yielder;
///   xSemaphoreGiveFromISR(semaphore, yielder);
///   // `yielder` will automatically clean up when this handler returns
/// }
/// \endcode
///
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
