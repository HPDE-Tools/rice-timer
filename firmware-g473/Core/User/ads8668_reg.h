// Copyright (c) rice-timer authors
#pragma once

#include <array>
#include <cstdint>

enum class Ads8668Command : uint16_t {
  kNoop = 0x0000,
  kStdby = 0x8200,
  kPwrDn = 0x8300,
  kRst = 0x8500,
  kAutoRst = 0xA000,
  kManAux = 0xE000,
};

constexpr uint16_t Ads8668ManChCommand(uint8_t ch) {
  return 0xC000 + 0x400 * ch;
}

enum class Ads8668Reg : uint8_t {
  kAutoSeqEn = 0x01,
  kChannelPowerDown = 0x02,
  kFeatureSelect = 0x03,
};

constexpr uint8_t Ads8668RangeReg(uint8_t ch) {
  return 0x05 + ch;
}

enum class Ads8668Range : uint8_t {
  kBipolar2p5 = 0b0000,
  kBipolar1p25 = 0b0001,
  kBipolar0p625 = 0b0010,
  kBipolar0p3125 = 0b0011,
  kBipolar0p15625 = 0b1011,
  kUnipolar2p5 = 0b0101,
  kUnipolar1p25 = 0b0110,
  kUnipolar0p625 = 0b0111,
  kUnipolar0p3125 = 0b1111,
};
