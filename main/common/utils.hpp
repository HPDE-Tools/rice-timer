#pragma once

#include <cstdint>
#include <type_traits>

constexpr char HexDigitLower(uint8_t i) { return "0123456789abcdef"[i]; }
constexpr char HexDigitUpper(uint8_t i) { return "0123456789ABCDEF"[i]; }

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
