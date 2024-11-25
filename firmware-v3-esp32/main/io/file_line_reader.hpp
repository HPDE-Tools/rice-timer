// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <cstdio>
#include <memory>
#include <optional>
#include <string_view>

#include "common/iter.hpp"

namespace io {

// NOTE: ASCII only

class FileLineReaderImpl {
 public:
  using Item = std::string_view;
  FileLineReaderImpl(FILE* f, int max_line_size, char sep = '\n');

  std::optional<std::string_view> Next();

 private:
  FILE* f_;  // not owned
  std::unique_ptr<char[]> buf_;
  int size_;
  int begin_;
  int end_;
  char sep_;

  bool FillBuffer();
};

using FileLineReader = RustIter<FileLineReaderImpl>;

}  // namespace io
