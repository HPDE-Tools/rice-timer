// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>
#include <optional>

#include "driver/gpio.h"
#include "driver/pcnt.h"
#include "esp_err.h"

#include "common/macros.hpp"

/// Configure one PCNT unit to track one incremental / quadrature / 2-bit gray encoder in 4x mode
/// (i.e. all edges are counted => 4 counts per period).
///
/// When Phase A leads Phase B, counter increases.
/// When Phase B leads Phase A, counter decreases.
///
/// @example
///    <--- decrease   increase --->
///         _____       _____
/// A    __|     |_____|     |_____
///            _____       _____
/// B    _____|     |_____|     |__
///
class Encoder {
 public:
  struct Option {
    pcnt_unit_t unit;
    gpio_num_t a_pin;       // leading phase for count increase
    gpio_num_t b_pin;       // trailing phase for count increase
    uint16_t filter_value;  // 0 <= filter_value < 1024
  };

  std::optional<int16_t> count() const;

  DEFINE_CREATE(Encoder)

 private:
  Option option_;

  explicit Encoder(Option option);
  esp_err_t Setup();
};
