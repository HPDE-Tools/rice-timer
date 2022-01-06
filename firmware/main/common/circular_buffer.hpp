// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "fmt/core.h"
#include "fmt/format.h"

#include "common/macros.hpp"
#include "common/polyfill.hpp"

/// Circular buffer implemented as a fixed, heap-allocated array.
/// When full, the next incoming element will take the place of the oldest one.
/// Not thread-safe.
template <typename T>
class CircularBuffer {
 public:
  explicit CircularBuffer(int capacity)
      : data_(std::make_unique<T[]>(capacity)), capacity_(capacity) {}

  // TODO(summivox): add a way to allow default construction, then later assign capacity

  bool empty() const { return size_ <= 0; }
  bool full() const { return size_ >= capacity_; }
  const T* data() const { return data_.get(); }
  T* data() { return data_.get(); }
  int capacity() const { return capacity_; }
  int size() const { return size_; }

  void clear() {
    size_ = 0;
    front_i_ = 0;
    back_i_ = 0;
  }

  const T& operator[](int i) const { return data_[RealIndex(i)]; }
  T& operator[](int i) { return data_[RealIndex(i)]; }

  const T& front() const { return data_[front_i_]; }
  T& front() { return data_[front_i_]; }
  const T& back() const { return data_[RealIndex(-1)]; }
  T& back() { return data_[RealIndex(-1)]; }

  T pop_front() {
    T popped{std::move(data_[front_i_])};
    IncFront();
    return popped;
  }

  void push_back(const T& elem) {
    data_[back_i_] = elem;
    IncBack();
  }
  void push_back(T&& elem) {
    data_[back_i_] = std::forward<T>(elem);
    IncBack();
  }

  template <typename... Args>
  T& emplace_back(Args&&... args) {
    if (full()) {
      (data_.get() + back_i_)->~T();
    }
    T* elem = new (data_.get() + back_i_) T(std::forward<Args>(args)...);
    IncBack();
    return *elem;
  }

  T& recycle_back() {
    T& elem = data_[back_i_];
    IncBack();
    return elem;
  }

  void Dump(bool dump_data = true) {
    fmt::print("Circular{{m={} n={} f={} b={}", capacity_, size_, front_i_, back_i_);
    if (dump_data) {
      fmt::print(" data={{{}}}", fmt::join(data_.get(), data_.get() + capacity_, ", "));
    }
    fmt::print("}}\n");
  }

  NOT_COPYABLE_NOR_MOVABLE(CircularBuffer)

 private:
  std::unique_ptr<T[]> data_;
  int capacity_;
  int size_ = 0;
  int front_i_ = 0;
  int back_i_ = 0;

  int RealIndex(int i) const noexcept {
    if (i >= 0) {
      const int j = front_i_ + i;
      return j < capacity_ ? j : j - capacity_;
    } else {
      const int j = back_i_ + i;
      return j >= 0 ? j : j + capacity_;
    }
  }

  void IncFront() noexcept {
    if (++front_i_ == capacity_) {
      front_i_ = 0;
    }
    --size_;
  }

  void IncBack() noexcept {
    if (++back_i_ == capacity_) {
      back_i_ = 0;
    }
    if (full()) {
      front_i_ = back_i_;
    } else {
      ++size_;
    }
  }
};
