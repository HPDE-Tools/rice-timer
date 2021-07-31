// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cmath>
#include <complex>
#include <cstdint>
#include <type_traits>

namespace std {

// Polyfill for std::lerp, std::midpoint
// https://github.com/emsr/cxx_linear

#if !defined(__cpp_lib_interpolate) || __cpp_lib_interpolate < 201902L
#define __cpp_lib_interpolate 201902L

template <typename _Float>
constexpr std::enable_if_t<std::is_floating_point_v<_Float>, _Float> lerp(
    _Float __a, _Float __b, _Float __t) {
  if (std::isnan(__a) || std::isnan(__b) || std::isnan(__t))
    return std::numeric_limits<_Float>::quiet_NaN();
  else if ((__a <= _Float{0} && __b >= _Float{0}) || (__a >= _Float{0} && __b <= _Float{0}))
  // ab <= 0 but product could overflow.
#ifndef FP_FAST_FMA
    return __t * __b + (_Float{1} - __t) * __a;
#else
    return std::fma(__t, __b, (_Float{1} - __t) * __a);
#endif
  else if (__t == _Float{1})
    return __b;
  else {  // monotonic near t == 1.
#ifndef FP_FAST_FMA
    const auto __x = __a + __t * (__b - __a);
#else
    const auto __x = std::fma(__t, __b - __a, __a);
#endif
    return (__t > _Float{1}) == (__b > __a) ? std::max(__b, __x) : std::min(__b, __x);
  }
}

template <typename _Int>
constexpr std::enable_if_t<std::is_integral_v<_Int> && !std::is_same_v<_Int, bool>, _Int> midpoint(
    _Int __a, _Int __b) noexcept {
  using _UInt = std::make_unsigned_t<_Int>;
  /*
        const auto __ua = _UInt(__a);
        const auto __ub = _UInt(__b);
        const auto __del = (__ub > __ua ? +(__ub - __ua) : -(__ua - __ub));
        return _Int(__ua + __del / 2);
  */
  return _Int(_UInt(__a) + (_UInt(__b) - _UInt(__a)) / 2);
}

// What about infinity?
template <typename _Float>
constexpr std::enable_if_t<std::is_floating_point_v<_Float>, _Float> midpoint(
    _Float __a, _Float __b) noexcept {
  if (std::isnan(__a) || std::isnan(__b))
    return std::numeric_limits<_Float>::quiet_NaN();
  else
    return std::isnormal(__a) && std::isnormal(__b) ? __a / 2 + __b / 2 : (__a + __b) / 2;
}

template <typename _Tp>
_Tp* midpoint(_Tp* __a, _Tp* __b) {
  // using _Iptr = std::intptr_t;
  // return static_cast<_Tp*>(__a + std::midpoint(_Iptr(__a), _Iptr(__b)));
  const auto __diff = (__b - __a) / 2;
  return __a + __diff;
}

template <typename _Float>
constexpr std::enable_if_t<std::is_floating_point_v<_Float>, std::complex<_Float>> lerp(
    const std::complex<_Float>& __a, const std::complex<_Float>& __b, _Float __t) {
  using __cmplx = std::complex<_Float>;
  return __cmplx(
      std::lerp(std::real(__a), std::real(__b), __t),
      std::lerp(std::imag(__a), std::imag(__b), __t));
}

template <typename _Float>
constexpr std::enable_if_t<std::is_floating_point_v<_Float>, std::complex<_Float>> midpoint(
    const std::complex<_Float>& __a, const std::complex<_Float>& __b) noexcept {
  using __cmplx = std::complex<_Float>;
  return __cmplx(
      std::midpoint(std::real(__a), std::real(__b)), std::midpoint(std::imag(__a), std::imag(__b)));
}

#endif  // __cpp_lib_interpolate

}  // namespace std
