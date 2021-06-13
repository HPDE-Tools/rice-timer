// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#define NON_COPYABLE_NOR_MOVABLE(T)    \
  T(T const&) = delete;                \
  void operator=(T const& t) = delete; \
  T(T&&) = delete;

#define DEFINE_CREATE(CLASS)                                         \
  template <typename... T>                                           \
  static std::unique_ptr<CLASS> Create(T&&... arg) {                 \
    std::unique_ptr<CLASS> self{new CLASS(std::forward<T>(arg)...)}; \
    if (self->Setup() != ESP_OK) {                                   \
      self.reset();                                                  \
    }                                                                \
    return self;                                                     \
  }
