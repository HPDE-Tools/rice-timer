// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <memory>
#include <type_traits>

constexpr char HexDigitLower(uint8_t i) { return "0123456789abcdef"[i & uint8_t{0xf}]; }
constexpr char HexDigitUpper(uint8_t i) { return "0123456789ABCDEF"[i & uint8_t{0xf}]; }

template <typename T>
constexpr auto SignedMinus(T a, T b) -> std::make_signed_t<T> {
  return static_cast<std::make_signed_t<T>>(a - b);
}

// https://en.cppreference.com/w/cpp/utility/variant/visit
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

// usually not zero-sized, but good enough
struct Unit {};

constexpr uint16_t Uint16LeAt(const uint8_t* bytes) {
  return static_cast<uint16_t>(
      static_cast<uint16_t>(bytes[0]) | (static_cast<uint16_t>(bytes[1]) << uint16_t{8}));
}
constexpr int16_t Sint16LeAt(const uint8_t* bytes) {
  return static_cast<int16_t>(
      static_cast<uint16_t>(bytes[0]) | (static_cast<uint16_t>(bytes[1]) << uint16_t{8}));
}
