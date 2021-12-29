// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <sys/time.h>
#include <cstdint>
#include <ctime>
#include <type_traits>

#include "fmt/chrono.h"

#include "common/utils.hpp"

// Time point conventions in this project:
//
// | type       | category name      | what it means                           |
// |------------|--------------------|-----------------------------------------|
// | tm         | zulu               | UTC date and time as fields in a struct |
// | time_t     | unix               | whole seconds since unix epoch          |
// | timeval    | unix (with us)     | seconds + microseconds since unix epoch |
// | TickType_t | ostime             | OS ticks since boot (rolling)           |
// | uint32_t   | capture            | high-freq MCPWM capture timer (rolling) |

using TimeZulu = tm;
using TimeUnix = time_t;
using TimeUnixWithUs = timeval;

//////////////////////////////////////////

/// Build TimeZulu (`struct tm`) from numbers literally from each field in ISO-8601.
/// This is to avoid confusion in different calendar packing conventions (such as tm itself!).
///
/// \param year_yyyy 4-digit year, 0000 ~ 9999
/// \param month_1_to_12 2-digit month of year, 01 (Jan) ~ 12 (Dec)
/// \param day_1_to_31 2-digit day of month, 01 ~ 31
/// \param hour_hh 2-digit hour, 00 ~ 23
/// \param minute_mm 2-digit minute, 00 ~ 59
/// \param second_ss 2-digit second, 00 ~ 60 (60 = leap second)
constexpr TimeZulu ZuluFromParts(
    int32_t year_yyyy,
    int32_t month_1_to_12,
    int32_t day_1_to_31,
    int32_t hour_hh,
    int32_t minute_mm,
    int32_t second_ss) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  return TimeZulu{
      .tm_sec = second_ss,
      .tm_min = minute_mm,
      .tm_hour = hour_hh,
      .tm_mday = day_1_to_31,
      .tm_mon = month_1_to_12 - 1,
      .tm_year = year_yyyy - 1900,
  };
#pragma GCC diagnostic pop
}

/////////////////////////////////////////////////////////////

inline TimeUnix ToUnix(TimeZulu t_zulu) { return mktime(&t_zulu); }
inline TimeUnix ToUnixAndNormalize(TimeZulu& t_zulu) { return mktime(&t_zulu); }
inline TimeUnixWithUs ToUnix(TimeZulu t_zulu, int32_t dt_us) {
  return {
      .tv_sec = ToUnix(t_zulu),
      .tv_usec = dt_us,
  };
}

inline TimeZulu ToZulu(TimeUnix t_unix) { return fmt::gmtime(t_unix); }
inline TimeZulu ToZulu(TimeUnixWithUs t_unix) { return fmt::gmtime(t_unix.tv_sec); }
inline TimeZulu ToZulu(timespec t_unix) { return fmt::gmtime(t_unix.tv_sec); }

constexpr int64_t ToMicroseconds(const TimeUnixWithUs& t_unix) {
  return int64_t{t_unix.tv_sec} * int64_t{1'000'000} + int64_t{t_unix.tv_usec};
}
constexpr int64_t ToMilliseconds(const TimeUnixWithUs& t_unix) {
  return int64_t{t_unix.tv_sec} * int64_t{1'000} + int64_t{t_unix.tv_usec} / int64_t{1'000};
}
constexpr int64_t operator-(const TimeUnixWithUs& a, const TimeUnixWithUs& b) {
  return ToMicroseconds(a) - ToMicroseconds(b);
}

//////////////////////////////////////////////////////////////

constexpr uint16_t ToFat32Date(const TimeZulu& t_zulu) {
  // bit15:9
  //     Year origin from 1980 (0..127)
  // bit8:5
  //     Month (1..12)
  // bit4:0
  //     Day (1..31)
  return (((t_zulu.tm_year + (1900 - 1980)) & 0x7f) << 9) | ((t_zulu.tm_mon & 0xf) << 5) |
         ((t_zulu.tm_mday & 0x1f) << 0);
}

constexpr uint16_t ToFat32Time(const TimeZulu& t_zulu) {
  // bit15:11
  //     Hour (0..23)
  // bit10:5
  //     Minute (0..59)
  // bit4:0
  //     Second / 2 (0..29)
  return ((t_zulu.tm_hour & 0x1f) << 11) | ((t_zulu.tm_min & 0x3f) << 5) |
         (((t_zulu.tm_sec / 2) & 0x1f) << 0);
}

/////////////////////////////////////////////////////////

inline TimeUnix NowUnix() { return time(nullptr); }
inline TimeUnixWithUs NowUnixWithUs() {
  TimeUnixWithUs ret;
  gettimeofday(&ret, /*tz*/ nullptr);
  return ret;
}
inline int64_t NowUnixMs() { return ToMilliseconds(NowUnixWithUs()); }
inline int64_t NowUnixUs() { return ToMicroseconds(NowUnixWithUs()); }
inline TimeZulu NowZulu() { return ToZulu(NowUnix()); }

////////////////////////////////////////////////////////
