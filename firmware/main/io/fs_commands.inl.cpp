// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <map>

#include "common/console_command.hpp"
#include "io/fs_utils.hpp"

namespace {
const std::map<uint8_t, std::string> kDirentTypeName{
    {DT_REG, "DT_REG"},
    {DT_DIR, "DT_DIR"},
    {DT_UNKNOWN, "DT_UNKNOWN"},
};
}  // namespace

DEFINE_CONSOLE_COMMAND(
    ls,
    "list all directories and files under given path",
    /*hint*/ nullptr,
    { arg_str* path = arg_str1(nullptr, nullptr, "<path>", "path to list"); },
    /*num_end*/ 1) {
  CHECK(path->count == 1);

  std::string dir = path->sval[0];

  fputs("\n", stdout);
  for (dirent* p : io::DirIter(dir.c_str())) {
    printf("name='%s' type=%d (%s)", p->d_name, p->d_type, kDirentTypeName.at(p->d_type).c_str());
    // if (p->d_type == DT_REG) {
    struct stat s {};
    stat((dir + "/" + p->d_name).c_str(), &s);
    TimeParts mt = ToParts(s.st_mtim);
    printf(" size=%d", (int)s.st_size);
    // st_ctim is not populated, and we don't have st_birthtim / st_birthtimespec
    printf(
        " mtim=%04d-%02d-%02d_%02d:%02d:%02d",
        mt.tm_year + 1900,
        mt.tm_mon + 1,
        mt.tm_mday,
        mt.tm_hour,
        mt.tm_min,
        mt.tm_sec);
    // }
    fputs("\n", stdout);
  }
  fputs("\n", stdout);

  return 0;
}
