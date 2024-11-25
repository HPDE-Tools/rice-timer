// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "common/perf.hpp"

#include <algorithm>

#include "fmt/core.h"

void PerfCollector::Dump() const {
  fmt::print(
      "PERF_{} [{}]\n",
      name_,
      fmt::join(buf_.data(), buf_.data() + std::min(4, buf_.capacity()), ","));
}
