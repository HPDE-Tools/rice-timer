// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// NOTE(summivox): This provides polyfill for C++20 library features potentially missing in the
// current ESP32 GCC toolchain.

#pragma once

#include <memory>
#include <type_traits>

namespace std {

#if !defined(__cpp_lib_bounded_array_traits) || __cpp_lib_bounded_array_traits < 201902
#define __cpp_lib_bounded_array_traits 201902L

// STRUCT TEMPLATE is_bounded_array
template <class>
inline constexpr bool is_bounded_array_v = false;

template <class _Ty, size_t _Nx>
inline constexpr bool is_bounded_array_v<_Ty[_Nx]> = true;

template <class _Ty>
struct is_bounded_array : bool_constant<is_bounded_array_v<_Ty>> {};

// STRUCT TEMPLATE is_unbounded_array
template <class>
inline constexpr bool is_unbounded_array_v = false;

template <class _Ty>
inline constexpr bool is_unbounded_array_v<_Ty[]> = true;

template <class _Ty>
struct is_unbounded_array : bool_constant<is_unbounded_array_v<_Ty>> {};

#endif  // __cpp_lib_bounded_array_traits

#if !defined(__cpp_lib_smart_ptr_for_overwrite) || __cpp_lib_smart_ptr_for_overwrite < 202002
#define __cpp_lib_smart_ptr_for_overwrite 202002L

// FUNCTION TEMPLATE make_unique_for_overwrite
template <class _Ty, enable_if_t<!is_array_v<_Ty>, int> = 0>
[[nodiscard]] unique_ptr<_Ty>
make_unique_for_overwrite() {  // make a unique_ptr with default initialization
  return unique_ptr<_Ty>(new _Ty);
}

template <class _Ty, enable_if_t<is_unbounded_array_v<_Ty>, int> = 0>
[[nodiscard]] unique_ptr<_Ty> make_unique_for_overwrite(
    const size_t _Size) {  // make a unique_ptr with default initialization
  using _Elem = remove_extent_t<_Ty>;
  return unique_ptr<_Ty>(new _Elem[_Size]);
}

template <class _Ty, class... _Types, enable_if_t<is_bounded_array_v<_Ty>, int> = 0>
void make_unique_for_overwrite(_Types&&...) = delete;

#endif  // __cpp_lib_smart_ptr_for_overwrite

}  // namespace std
