// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "common/macros.hpp"

template <typename T>
class RustMutex;
template <typename T>
class RustMutexGuard;

/// Rust-styled mutex-protected object wrapper
/// Usage: `auto guard = mutex.Lock();`, then use `guard` as a `T*`.
template <typename T>
class RustMutex final {
 public:
  using DataType = T;
  friend class RustMutexGuard<T>;

  template <typename... Arg>
  explicit RustMutex(Arg&&... arg) : data_{std::forward<Arg>(arg)...} {
    xSemaphoreCreateMutexStatic(&mutex_buf_);
  }
  ~RustMutex() { vSemaphoreDelete(mutex()); }

  SemaphoreHandle_t mutex() { return reinterpret_cast<SemaphoreHandle_t>(&mutex_buf_); }

  RustMutexGuard<T> Lock(TickType_t timeout = portMAX_DELAY) { return {this, timeout}; }

 private:
  T data_;
  StaticSemaphore_t mutex_buf_;
};

template <typename T>
class RustMutexGuard final {
 public:
  using DataType = T;
  friend class RustMutex<T>;

  ~RustMutexGuard() { xSemaphoreGive(mutex_); }

  T& operator*() const noexcept { return *data_; }
  T* operator->() const noexcept { return data_; }

  // NOTE: this works because RVO is guaranteed
  NOT_COPYABLE_NOR_MOVABLE(RustMutexGuard<T>)

 private:
  T* data_;
  SemaphoreHandle_t mutex_;

  RustMutexGuard(RustMutex<T>* parent, TickType_t timeout)
      : data_(&parent->data_), mutex_(parent->mutex()) {
    xSemaphoreTake(mutex_, timeout);
  }
};
