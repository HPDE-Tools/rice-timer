// Copyright 2022 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "argtable3/argtable3.h"

#include "common/console_command_registry.hpp"

#define DEFINE_CONSOLE_COMMAND(name, help_str, hint_str, argtable_struct_body, num_end)         \
  struct Argtable_##name argtable_struct_body;                                                  \
  struct ConsoleCommand_##name : public Argtable_##name {                                       \
    static constexpr char TAG[] = #name;                                                        \
    struct arg_end* end = arg_end(num_end);                                                     \
    int Run(int argc, char** argv) {                                                            \
      if (const int num_errors = arg_parse(argc, argv, reinterpret_cast<void**>(this));         \
          num_errors > 0) {                                                                     \
        arg_print_errors(stderr, this->end, argv[0]);                                           \
        return 1;                                                                               \
      }                                                                                         \
      return RunInternal(argc, argv);                                                           \
    }                                                                                           \
    int RunInternal(int argc, char** argv);                                                     \
  } g_console_command_##name;                                                                   \
                                                                                                \
  static bool ConsoleCommandRegisterer_##name() {                                               \
    ConsoleCommandRegistry* registry = ConsoleCommandRegistry::GetInstance();                   \
    if (!registry) {                                                                            \
      return false;                                                                             \
    }                                                                                           \
    registry->AddCommand({                                                                      \
        .command = #name,                                                                       \
        .help = help_str,                                                                       \
        .hint = hint_str,                                                                       \
        .func = [](int argc, char** argv) { return g_console_command_##name.Run(argc, argv); }, \
        .argtable = reinterpret_cast<void**>(&g_console_command_##name),                        \
    });                                                                                         \
    return true;                                                                                \
  }                                                                                             \
  static bool g_console_command_registerer_result_##name = ConsoleCommandRegisterer_##name();   \
                                                                                                \
  int ConsoleCommand_##name::RunInternal(int argc, char** argv)
