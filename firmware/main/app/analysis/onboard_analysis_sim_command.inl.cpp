#include <algorithm>
#include <charconv>
#include <cinttypes>
#include <string>
#include <string_view>
#include <vector>

#include "app/logger_instance.hpp"
#include "common/console_command.hpp"
#include "common/iter.hpp"
#include "common/polyfill.hpp"
#include "common/times.hpp"
#include "device/gps_utils.hpp"
#include "io/file_line_reader.hpp"

namespace app {

struct LogEntryGps {
  uint32_t capture;
  ParsedNmea nmea;
};

struct LogEntryRawImu {
  uint32_t capture;
  std::array<int32_t, 6> raw_imu;
};

#if 0
struct LogEntryCan {
  uint32_t capture;
  twai_message_t message;
};
#endif

using LogEntry = std::variant<char, LogEntryGps, LogEntryRawImu /*, LogEntryCan*/>;

class LogIteratorImpl {
 public:
  static constexpr int kBufSize = 1024;

  using Item = LogEntry;
  LogIteratorImpl(FILE* f) : line_reader_(f, kBufSize) {}

  std::optional<LogEntry> Next() {
    std::optional<LogEntry> result{};
    const std::optional<std::string_view> line = line_reader_.Next();
    if (!line) {
      ESP_LOGE("", "no more lines!");
      return result;
    }
    if (line->empty()) {
      // ESP_LOGE("", "empty line!");
      // skip empty lines --- do not terminate
      result.emplace('\0');
      return result;
    }
    const char typechar = (*line)[0];
    const char* const begin = line->data() + 2;
    const char* const end = line->data() + line->size();
    // ESP_LOGE("", "typechar: %c", typechar);
    switch (typechar) {
      case 'g': {
        result.emplace();
        LogEntryGps& g = result->emplace<LogEntryGps>();
        const char* p = std::from_chars(begin, end, g.capture).ptr;
        if (p == begin) {
          result.reset();
          return result;
        }
        g.nmea = ParseNmea(std::string(line->substr(p - line->data() + 1)));
        break;
      }
      case 'i': {
        result.emplace();
        LogEntryRawImu r = result->emplace<LogEntryRawImu>();
        const char* p = begin;
        p = std::from_chars(p, end, r.capture).ptr;
        p = std::from_chars(p, end, r.raw_imu[0]).ptr;
        p = std::from_chars(p, end, r.raw_imu[1]).ptr;
        p = std::from_chars(p, end, r.raw_imu[2]).ptr;
        p = std::from_chars(p, end, r.raw_imu[3]).ptr;
        p = std::from_chars(p, end, r.raw_imu[4]).ptr;
        p = std::from_chars(p, end, r.raw_imu[5]).ptr;
        break;
      }
      default:
        result.emplace(typechar);
        break;
    }
    return result;
  }

 private:
  io::FileLineReaderImpl line_reader_;
};

using LogIterator = RustIter<LogIteratorImpl>;

DEFINE_CONSOLE_COMMAND(
    ls_session, "Lists all sessions logged by the current device", nullptr, {}, 1) {
  std::vector<int64_t> session_ids;
  for (const dirent* entry : io::DirIter(g_device_dir)) {
    if (entry->d_type != DT_DIR) {
      continue;
    }
    const int64_t id = atoll(entry->d_name);
    session_ids.push_back(id);
  }
  std::sort(session_ids.begin(), session_ids.end());
  printf(
      "\n"
      "sessions:\n");
  for (auto id : session_ids) {
    printf("%" PRId64 "\n", id);
  }
  printf("\n");
  return 0;
}

DEFINE_CONSOLE_COMMAND(
    sim,
    "Simulates a log by replaying it through the onboard analysis module.",
    nullptr,
    {
      arg_int* session =
          arg_int0("s", "session", "<session id>", "Session ID of the log to be replayed");
      arg_file* input_path = arg_file0(
          "i",
          "input",
          "<input log path>",
          "Absolute path of the log to be replayed (overrides session ID); e.g. \"/BD2AA7C0/123\"; "
          "Has priority over `--session`.");
      arg_str* output_path =
          arg_str0("o", "output", "<output file>", "Output file for storing the results");
    },
    1) {
  std::string input_path_str;
  if (input_path->count) {
    input_path_str = input_path->filename[0];
  } else if (session->count) {
    input_path_str = g_device_dir + "/" + std::to_string(session->ival[0]);
  } else {
    ESP_LOGE(TAG, "Need either `--session` or `-input`");
    return 1;
  }

  std::string output_path_str;
  if (output_path->count) {
    output_path_str = output_path->sval[0];
  } else {
    output_path_str = input_path_str + ".sim";
  }
  ESP_LOGI(TAG, "input path: %s", input_path_str.c_str());
  ESP_LOGI(TAG, "output path: %s", output_path_str.c_str());

  std::vector<int> split_dir_ids;
  for (const dirent* entry : io::DirIter(input_path_str)) {
    if (entry->d_type != DT_DIR) {
      continue;
    }
    ESP_LOGW(TAG, "found dir: %s", entry->d_name);
    const int id = atoi(entry->d_name);
    split_dir_ids.push_back(id);
  }
  std::sort(split_dir_ids.begin(), split_dir_ids.end());

  std::vector<std::string> split_paths;
  for (const int split_dir_id : split_dir_ids) {
    const std::string split_dir = input_path_str + "/" + std::to_string(split_dir_id);
    ESP_LOGW(TAG, "exploring dir: %s", split_dir.c_str());
    std::vector<int64_t> split_ids;
    for (const dirent* entry : io::DirIter(split_dir)) {
      if (entry->d_type != DT_REG) {
        continue;
      }
      const std::string_view name = entry->d_name;
      ESP_LOGW(TAG, "found file: %s", name.data());
      auto dot_index = name.rfind(".");
      if (dot_index == name.npos || name.substr(dot_index + 1) != "log") {
        continue;
      }
      const int64_t id = atoll(name.data());
      split_ids.push_back(id);
    }
    std::sort(split_ids.begin(), split_ids.end());
    for (const auto split_id : split_ids) {
      split_paths.push_back(split_dir + "/" + std::to_string(split_id) + ".log");
    }
  }

  int64_t num_lines = 0;
  for (const std::string& split_path : split_paths) {
    ESP_LOGW(TAG, "reading split file: %s", split_path.c_str());
    io::OwnedFile file = io::OpenFile(split_path, "r");
    for (const auto& log_entry : LogIterator(file.get())) {
      ++num_lines;
      if (num_lines % 1000 == 0) {
        printf("=== %" PRId64 "\n", num_lines);
      }
      std::visit(
          overloaded{
              [](const LogEntryGps& gps) {
                // ESP_LOGW(TAG, "is GPS");
                const auto t = GetTimeFromNmea(gps.nmea);
                if (t) {
                  const TimeParts mt = ToParts(*t);
                  ESP_LOGE(
                      TAG,
                      "%04d-%02d-%02d %02d:%02d:%02d",
                      mt.tm_year + 1900,
                      mt.tm_mon + 1,
                      mt.tm_mday,
                      mt.tm_hour,
                      mt.tm_min,
                      mt.tm_sec);
                }
              },
              [](char c) {
                // ESP_LOGW(TAG, "is %c", c);
              },
              [](const auto& unused) {
                // ESP_LOGW(TAG, "is something else");
              },
          },
          log_entry);
    }
  }

  return 0;
}

}  // namespace app
