// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#define NON_COPYABLE_NOR_MOVABLE(T)    \
  T(T const&) = delete;                \
  void operator=(T const& t) = delete; \
  T(T&&) = delete;
