#pragma once

#include "common/logging.hpp"
#include "common/scope_guard.hpp"

constexpr char HexDigitLower(uint8_t i) { return "0123456789abcdef"[i]; }
constexpr char HexDigitUpper(uint8_t i) { return "0123456789ABCDEF"[i]; }
