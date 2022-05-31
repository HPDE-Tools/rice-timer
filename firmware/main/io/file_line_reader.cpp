// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <algorithm>
#include <cstring>

#include "common/macros.hpp"
#include "io/file_line_reader.hpp"

namespace io {

FileLineReaderImpl::FileLineReaderImpl(FILE* f, int max_line_size, char sep)
    : f_(f),
      buf_{std::make_unique<char[]>(max_line_size)},
      size_(max_line_size),
      begin_(0),
      end_(0),
      sep_(sep) {
  FillBuffer();
}

std::optional<std::string_view> FileLineReaderImpl::Next() {
  // ESP_LOGI("", "[%d, %d)", begin_, end_);
  if (begin_ == end_ && feof(f_)) {
    return {};
  }
  const int next = std::min(end_, std::find(&buf_[begin_], &buf_[end_], sep_) - &buf_[0] + 1);
  if (next < end_ || begin_ == 0) {
    // found separator, or we have an oversized line (buffer already maxed out)
    const std::string_view result(&buf_[begin_], next - begin_);
    begin_ = next;
    return result;
  }
  // did not find separator but we should try again after eliminating the gap
  // at the begin of the buffer
  FillBuffer();
  return Next();
}

bool FileLineReaderImpl::FillBuffer() {
  if (begin_) {
    memmove(&buf_[0], &buf_[begin_], end_ - begin_);
    end_ -= begin_;
    begin_ = 0;
  }
  if (end_ < size_) {
    const int read_size = fread(&buf_[end_], 1, size_ - end_, f_);
    end_ += read_size;
  }
  return feof(f_);
}

}  // namespace io
