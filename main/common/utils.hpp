// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <array>
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
      (static_cast<uint16_t>(bytes[0]) << uint16_t{0}) |
      (static_cast<uint16_t>(bytes[1]) << uint16_t{8}));
}
constexpr uint16_t Uint16BeAt(const uint8_t* bytes) {
  return static_cast<uint16_t>(
      (static_cast<uint16_t>(bytes[0]) << uint16_t{8}) |
      (static_cast<uint16_t>(bytes[1]) << uint16_t{0}));
}
constexpr uint32_t Uint32LeAt(const uint8_t* bytes) {
  return static_cast<uint32_t>(
      (static_cast<uint32_t>(bytes[0]) << uint32_t{0}) |
      (static_cast<uint32_t>(bytes[1]) << uint32_t{8}) |
      (static_cast<uint32_t>(bytes[2]) << uint32_t{16}) |
      (static_cast<uint32_t>(bytes[3]) << uint32_t{24}));
}
constexpr uint32_t Uint32BeAt(const uint8_t* bytes) {
  return static_cast<uint32_t>(
      (static_cast<uint32_t>(bytes[0]) << uint32_t{24}) |
      (static_cast<uint32_t>(bytes[1]) << uint32_t{16}) |
      (static_cast<uint32_t>(bytes[2]) << uint32_t{8}) |
      (static_cast<uint32_t>(bytes[3]) << uint32_t{0}));
}

static_assert(Uint16LeAt(std::array<uint8_t, 2>{0x12u, 0x34u}.data()) == 0x3412u);
static_assert(Uint16BeAt(std::array<uint8_t, 2>{0x12u, 0x34u}.data()) == 0x1234u);
static_assert(Uint32LeAt(std::array<uint8_t, 4>{0x12u, 0x34u, 0x56u, 0x78u}.data()) == 0x78563412u);
static_assert(Uint32BeAt(std::array<uint8_t, 4>{0x12u, 0x34u, 0x56u, 0x78u}.data()) == 0x12345678u);

constexpr int16_t Sint16LeAt(const uint8_t* bytes) {
  return static_cast<int16_t>(Uint16LeAt(bytes));
}
constexpr int16_t Sint16BeAt(const uint8_t* bytes) {
  return static_cast<int16_t>(Uint16BeAt(bytes));
}
constexpr int32_t Sint32LeAt(const uint8_t* bytes) {
  return static_cast<int32_t>(Uint32LeAt(bytes));
}
constexpr int32_t Sint32BeAt(const uint8_t* bytes) {
  return static_cast<int32_t>(Uint32BeAt(bytes));
}

/// comma-separated little-endian bytes of a 16-bit integer (no trailing comma)
#define UINT16_LE_BYTES(x) uint8_t(x), uint8_t(((x) >> 8))
/// comma-separated little-endian bytes of a 32-bit integer (no trailing comma)
#define UINT32_LE_BYTES(x) uint8_t(x), uint8_t((x) >> 8), uint8_t((x) >> 16), uint8_t((x) >> 24)

/// comma-separated big-endian bytes of a 16-bit integer (no trailing comma)
#define UINT16_BE_BYTES(x) uint8_t(((x) >> 8)), uint8_t(x)
/// comma-separated big-endian bytes of a 32-bit integer (no trailing comma)
#define UINT32_BE_BYTES(x) uint8_t((x) >> 24), uint8_t((x) >> 16), uint8_t((x) >> 8), uint8_t(x)

static_assert(Uint16LeAt(std::array<uint8_t, 2>{UINT16_LE_BYTES(0x1234)}.data()) == 0x1234u);
static_assert(Uint16BeAt(std::array<uint8_t, 2>{UINT16_BE_BYTES(0x1234)}.data()) == 0x1234u);
static_assert(
    Uint32LeAt(std::array<uint8_t, 4>{UINT32_LE_BYTES(0x12345678)}.data()) == 0x12345678u);
static_assert(
    Uint32BeAt(std::array<uint8_t, 4>{UINT32_BE_BYTES(0x12345678)}.data()) == 0x12345678u);

// http://shimpossible.blogspot.com/2013/08/containerof-and-offsetof-in-c.html

template <typename P, typename M>
constexpr size_t OffsetOf(const M P::*member) {
  return (size_t) & (reinterpret_cast<P*>(0)->*member);
}

template <typename P, typename M>
constexpr P* ContainerOf(M* ptr, const M P::*member) {
  return (P*)((char*)ptr - OffsetOf(member));
}
