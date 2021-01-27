#pragma once

#include "common/logging.hpp"
#include "common/scope_guard.hpp"

constexpr char HexDigitLower(uint8_t i) { return i < 10 ? '0' + i : ('a' - 10) + i; }
constexpr char HexDigitUpper(uint8_t i) { return i < 10 ? '0' + i : ('A' - 10) + i; }
