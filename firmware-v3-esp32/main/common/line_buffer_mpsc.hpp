// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>
#include <string_view>

#include "esp_attr.h"

#include "common/macros.hpp"

struct ringbuf;
typedef struct ringbuf ringbuf_t;

class LineBufferMpsc {
 public:
#if 0
  class LineGuard {
   public:
    ~LineGuard() { buf_->PopPeeked(line_); }
    operator std::string_view() const { return line_; }
    operator const std::string_view&() const { return line_; }

   private:
    LineGuard(std::string_view line, LineBufferMpsc* buf);
    std::string_view line_;
    LineBufferMpsc* buf_;

    NOT_COPYABLE_NOR_MOVABLE(LineGuard)
  };
#endif

  LineBufferMpsc(int size_bytes, int num_producers, char line_sep = '\n');
  virtual ~LineBufferMpsc();

  void Clear();

  IRAM_ATTR bool Push(int producer_id, std::string_view line_without_sep);

  IRAM_ATTR std::string_view Peek();
  IRAM_ATTR void PopPeeked(std::string_view peeked);

 private:
  ringbuf_t* ringbuf_;
  std::unique_ptr<char[]> buf_;
  int size_bytes_;
  int num_producers_;
  char line_sep_;

  char* begin_ = 0;
  char* end_ = 0;
  size_t chunk_size_ = 0;
};
