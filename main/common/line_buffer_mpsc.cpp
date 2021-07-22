// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "common/line_buffer_mpsc.hpp"

#include <algorithm>

#include "esp_log.h"
#include "ringbuf_c/ringbuf.h"

#include "common/macros.hpp"

LineBufferMpsc::LineBufferMpsc(int size_bytes, int num_producers, char line_sep)
    : size_bytes_(size_bytes), num_producers_(num_producers), line_sep_(line_sep) {
  size_t ringbuf_t_size{};
  ringbuf_get_sizes(num_producers, &ringbuf_t_size, nullptr);

  ringbuf_ = (ringbuf_t*)malloc(ringbuf_t_size);
  CHECK(ringbuf_ != nullptr);
  buf_ = std::make_unique<char[]>(size_bytes);
  CHECK(buf_);

  Clear();
}

LineBufferMpsc::~LineBufferMpsc() { free(ringbuf_); }

void LineBufferMpsc::Clear() {
  ringbuf_setup(ringbuf_, num_producers_, size_bytes_);
  for (int i = 0; i < num_producers_; i++) {
    (void)ringbuf_register(ringbuf_, i);
  }
  begin_ = 0;
  end_ = 0;
}

bool LineBufferMpsc::Push(int producer_id, std::string_view line_without_sep) {
  CHECK(0 <= producer_id && producer_id < num_producers_);
  const int offset = ringbuf_acquire_i(ringbuf_, producer_id, line_without_sep.size() + 1);
  if (offset < 0) {
    return false;
  }
  std::copy(line_without_sep.begin(), line_without_sep.end(), &buf_[offset]);
  buf_[offset + line_without_sep.size()] = line_sep_;
  ringbuf_produce_i(ringbuf_, producer_id);
  return true;
}

std::string_view LineBufferMpsc::Peek() {
  if (chunk_size_ == 0) {
    // load a new chunk (may contain multiple lines) from queue
    size_t offset{};
    chunk_size_ = ringbuf_consume(ringbuf_, &offset);
    if (chunk_size_ == 0) {
      return {};
    }
    begin_ = &buf_[offset];
    end_ = begin_ + chunk_size_;
  }
  char* sep = std::find(begin_, end_, line_sep_);
  if (sep < end_) {
    sep++;  // include the line separator in result
  }
  return std::string_view(begin_, sep - begin_);
}

void LineBufferMpsc::PopPeeked(std::string_view peeked) {
  if (peeked.empty()) {
    return;
  }
  begin_ += peeked.size();
  if (begin_ == end_ && chunk_size_ > 0) {
    // release the fully spent chunk
    ringbuf_release(ringbuf_, chunk_size_);
    chunk_size_ = 0;
  }
}
