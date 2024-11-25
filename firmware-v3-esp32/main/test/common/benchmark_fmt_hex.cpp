// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <algorithm>
#include <charconv>
#include <string_view>

#include "driver/twai.h"
#include "fmt/core.h"
#include "fmt/format.h"

#include "common/perf.hpp"
#include "common/utils.hpp"

#include "unity.h"  // must be included last

DEFINE_PERF(serialize_raw);
DEFINE_PERF(serialize_fmt);

namespace {

twai_message_t MakeMessage(int seed) {
  const uint8_t len = (uint32_t(seed * 6007)) % 9;
  TEST_ASSERT_LESS_OR_EQUAL(8, len);
  twai_message_t message{};
  // message.extd = 1;
  message.identifier = seed & 0x7ff;
  message.data_length_code = len;
  for (int i = 0; i < len; i++) {
    message.data[i] = (seed * 393143 + i * 790547) & 0xff;
  }
  return message;
}

IRAM_ATTR char* WriteHexUpper(char* s, uint32_t value, int len) {
  for (char* p = s + len - 1; p >= s; --p, value >>= 4) {
    *p = HexDigitUpper(value & 0xf);
  }
  return s + len;
}

IRAM_ATTR std::string_view SerializeRaw(uint32_t current_capture, const twai_message_t& message) {
  static char buf[] = "c,2147483647,b0b1b2b3,8,d0d1d2d3d4d5d6d7";
  char* const buf_begin = buf + 2;
  char* const buf_end = buf + sizeof(buf);

  const uint8_t dlc = std::min(message.data_length_code, uint8_t{8});

  char* p = buf_begin;
  p = std::to_chars(p, buf_end, current_capture, /*base*/ 10).ptr;
  *p++ = ',';
  p = WriteHexUpper(p, message.identifier, message.extd ? 8 : 3);
  *p++ = ',';
  *p++ = '0' + dlc;
  *p++ = ',';
  for (int i = 0; i < dlc; i++) {
    p = WriteHexUpper(p, message.data[i], 2);
  }
  *p++ = '\0';
  TEST_ASSERT_LESS_OR_EQUAL(buf_end - buf_begin, p - buf_begin);

  return std::string_view(buf, p - buf - 1);
}

IRAM_ATTR std::string_view SerializeFmt(uint32_t current_capture, const twai_message_t& message) {
  static fmt::basic_memory_buffer<char, 42> buf;
  buf.clear();
  if (message.extd) {
    fmt::format_to(
        std::back_inserter(buf),
        FMT_STRING("c,{},{:08X},{},{:02X}"),
        current_capture,
        message.identifier,
        message.data_length_code,
        fmt::join(message.data, message.data + message.data_length_code, ""));
  } else {
    fmt::format_to(
        std::back_inserter(buf),
        FMT_STRING("c,{},{:03X},{},{:02X}"),
        current_capture,
        message.identifier,
        message.data_length_code,
        fmt::join(message.data, message.data + message.data_length_code, ""));
  }
  return std::string_view(buf.data(), buf.size());
}

constexpr int kNumIterations = 100000;

int TestSerializeRaw() {
  SCOPE_PERF(serialize_raw);
  int s = 0;
  for (int i = 0; i < kNumIterations; i++) {
    const uint32_t capture = uint32_t(i) * 81919810u;
    const twai_message_t message = MakeMessage(i);
    const std::string_view result = SerializeRaw(capture, message);
    s += result[0];
    if (i == kNumIterations / 2) {
      fmt::print("{}\n", result);
    }
  }
  return s;
}

int TestSerializeFmt() {
  SCOPE_PERF(serialize_fmt);
  int s = 0;
  for (int i = 0; i < kNumIterations; i++) {
    const uint32_t capture = uint32_t(i) * 81919810u;
    const twai_message_t message = MakeMessage(i);
    const std::string_view result = SerializeFmt(capture, message);
    s += result[0];
    if (i == kNumIterations / 2) {
      fmt::print("{}\n", result);
    }
  }
  return s;
}

}  // namespace

TEST_CASE("Benchmark hex serialization", "[common]") {
  TestSerializeRaw();
  TestSerializeFmt();
  PERF_serialize_raw.Dump();
  PERF_serialize_fmt.Dump();
}
