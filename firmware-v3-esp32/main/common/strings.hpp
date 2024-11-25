// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <string_view>

inline std::string_view TrimPrefix(std::string_view s, const char* char_set = " \r\n\t") {
  std::string_view ret = s;
  size_t pos = s.find_first_not_of(char_set);
  if (pos == std::string_view::npos) {
    pos = s.size();
  }
  ret.remove_prefix(pos);
  return ret;
}

inline std::string_view TrimSuffix(std::string_view s, const char* char_set = " \r\n\t") {
  std::string_view ret = s;
  ret.remove_suffix(s.size() - (s.find_last_not_of(char_set) + 1));
  return ret;
}
