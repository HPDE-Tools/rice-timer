#pragma once

#define NON_COPYABLE_NOR_MOVABLE(T)    \
  T(T const&) = delete;                \
  void operator=(T const& t) = delete; \
  T(T&&) = delete;
