// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/logger.hpp"

#include <inttypes.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <utime.h>
#include <cstdio>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "esp_log.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "fmt/core.h"
#include "freertos/queue.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "app/priorities.hpp"
#include "common/logging.hpp"
#include "common/scope_guard.hpp"
#include "common/strings.hpp"
#include "common/times.hpp"
#include "filesystem.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "logger";

constexpr int kLoggerStackSize = 4096;

constexpr char kSessionIdKey[] = "session_id";
constexpr int kLoggerQueueSize = 32;
constexpr int kSplitPrefixMod = 1'000;
constexpr int kMaxNumSplits = 1'000'000;
constexpr int64_t kMaxNumLinesPerSplit = CONFIG_MAX_LINES_PER_FILE;

constexpr int kFlushPeriodMs = 1000;

constexpr mode_t kFsMode = 0777;

int64_t g_session_id = 0;
std::string g_session_dir{};
QueueHandle_t g_logger_queue{};

struct LogFile {
  FILE* file = nullptr;
  int64_t num_lines = 0;

  LogFile(FILE* file, int64_t num_lines) : file(file), num_lines(num_lines) {}
  LogFile(const LogFile& r) = delete;
  LogFile(LogFile&& r) {
    file = r.file;
    num_lines = r.num_lines;
    r.file = nullptr;
    r.num_lines = 0;
  }

  ~LogFile() {
    if (file) {
      ESP_LOGW(TAG, "closing log file");
      fclose(file);
    }
  }

  static std::unique_ptr<LogFile> Create(const std::string& path) {
    FILE* file = fopen(path.c_str(), "a");
    return file ? std::make_unique<LogFile>(file, 0) : nullptr;
  }

  esp_err_t Writeln(const std::string& line) {
    if (!file) {
      return ESP_ERR_INVALID_STATE;
    }
    if (fputs(line.c_str(), file) == EOF || fputc('\n', file) == EOF) {
      ESP_LOGE(TAG, "Writeln fail: %s", line.c_str());
      return ESP_FAIL;
    }
    num_lines++;
    return ESP_OK;
  }

  void Flush() { fs::ReallyFlush(file); }
};

esp_err_t NvsInit() {
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    // NVS partition was truncated and needs to be erased
    // Retry nvs_flash_init
    TRY(nvs_flash_erase());
    err = nvs_flash_init();
  }
  return err;
}

esp_err_t GetNewSessionId(int64_t* out_session_id) {
  TRY(NvsInit());

  nvs_handle_t nvs;
  TRY(nvs_open("storage", NVS_READWRITE, &nvs));
  SCOPE_EXIT { nvs_close(nvs); };
  esp_err_t read_result = nvs_get_i64(nvs, kSessionIdKey, out_session_id);
  if (read_result == ESP_ERR_NVS_NOT_FOUND) {
    *out_session_id = 0;
  } else {
    TRY(read_result);
    (*out_session_id)++;
  }
  TRY(nvs_set_i64(nvs, kSessionIdKey, *out_session_id));
  TRY(nvs_commit(nvs));
  return ESP_OK;
}

esp_err_t Mkdir(const std::string& dir) {
  // NOTE(summivox): condition not reversed
  ESP_LOGI(TAG, "Mkdir: %s", dir.c_str());
  int result = mkdir(dir.c_str(), kFsMode);
  return result == 0 || errno == EEXIST ? ESP_OK : ESP_FAIL;
}

esp_err_t SetupSessionDir(uint8_t mac[6], int64_t session_id, std::string* out_session_dir) {
  std::string device_dir =
      fmt::format(CONFIG_MOUNT_ROOT "/{:02X}{:02X}{:02X}{:02X}", mac[2], mac[3], mac[4], mac[5]);
  TRY(Mkdir(device_dir));
  *out_session_dir = fmt::format("{}/{}", device_dir, session_id);
  TRY(Mkdir(*out_session_dir));
  return ESP_OK;
}

esp_err_t SetupSplitDir(
    int split_prefix, const std::string& session_dir, std::string* out_split_dir) {
  *out_split_dir = fmt::format("{}/{}", session_dir, split_prefix);
  return Mkdir(*out_split_dir);
}

std::string SetupSplitFilename(int split_id) {
  const int split_prefix = split_id / kSplitPrefixMod;
  std::string split_dir;
  CHECK_OK(SetupSplitDir(split_prefix, g_session_dir, &split_dir));
  return fmt::format("{}/{}.txt", split_dir, split_id);
}

void UpdateFileTime(const std::string& filename, TimeUnix t_unix) {
  utimbuf buf{.actime = t_unix, .modtime = t_unix};
  if (esp_vfs_utime(filename.c_str(), &buf) != 0) {
    ESP_LOGE(TAG, "utimes(%s, %d) fail => %s", filename.c_str(), (int)t_unix, strerror(errno));
  }
}

}  // namespace

TaskHandle_t g_logger_task{};
uint8_t g_mac[6];

esp_err_t LoggerInit() {
  g_logger_queue = xQueueCreate(kLoggerQueueSize, sizeof(std::string));
  if (!g_logger_queue) {
    return ESP_FAIL;
  }
  TRY(esp_efuse_mac_get_default(g_mac));
  TRY(GetNewSessionId(&g_session_id));
  ESP_LOGI(TAG, "logger session id: %lld", g_session_id);  // (somehow PRId64 doesn't work)
  ESP_LOGI(
      TAG,
      "logger mac: %02X %02X %02X %02X %02X %02X",
      g_mac[0],
      g_mac[1],
      g_mac[2],
      g_mac[3],
      g_mac[4],
      g_mac[5]);  // (somehow PRId64 doesn't work)
  TRY(SetupSessionDir(g_mac, g_session_id, &g_session_dir));
  ESP_LOGI(TAG, "logger initialized");
  return ESP_OK;
}

esp_err_t LoggerStart() {
  if (!xTaskCreatePinnedToCore(
          LoggerTask,
          "logger",
          kLoggerStackSize,
          nullptr,
          kPriorityLogging,
          &g_logger_task,
          APP_CPU_NUM)) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

void LoggerStop() {
  if (g_logger_task) {
    vTaskDelete(g_logger_task);
    g_logger_task = nullptr;
  }
}

#if 1  // TODO(summivox): choose one tunneling implementation

esp_err_t SendToLogger(std::string&& moved_line, uint32_t timeout) {
  char* s = new char[moved_line.size() + 1];
  strcpy(s, moved_line.c_str());
  if (!xQueueSendToBack(g_logger_queue, &s, timeout)) {
    return ESP_ERR_TIMEOUT;
  }
  return ESP_OK;
}

static std::string PopFromQueue() {
  char* s = nullptr;
  CHECK(xQueueReceive(g_logger_queue, &s, portMAX_DELAY));
  CHECK(s != nullptr);
  std::string result{s};
  delete[] s;
  return result;
}

#else

esp_err_t SendToLogger(std::string&& moved_line, uint32_t timeout) {
  std::string* carrier = new std::string(moved_line);
  // fmt::print("SEND {} -> {}\n", (void*)carrier, *carrier);
  if (!xQueueSendToBack(g_logger_queue, &carrier, timeout)) {
    return ESP_ERR_TIMEOUT;
  }
  return ESP_OK;
}

static std::string PopFromQueue() {
  std::string* carrier = nullptr;
  CHECK(xQueueReceive(g_logger_queue, &carrier, portMAX_DELAY));
  CHECK(carrier != nullptr);
  // fmt::print("RECV {}\n", (void*)carrier);
  std::string result{std::move(*carrier)};
  delete carrier;
  return result;
}
#endif

void LoggerTask(void* /*unused*/) {
  ui::g_model.logger_session_id = g_session_id;
  SCOPE_EXIT { vTaskDelete(nullptr); };
  for (int split_id = 0; split_id < kMaxNumSplits; split_id++) {
    std::string filename = SetupSplitFilename(split_id);
    std::unique_ptr<LogFile> file = LogFile::Create(filename);
    if (!file) {
      return;
    }
    ui::g_model.logger_split_id = split_id;
    while (file->num_lines < kMaxNumLinesPerSplit) {
      std::string line = PopFromQueue();
      CHECK_OK(file->Writeln(line));
      ui::g_model.logger_lines = file->num_lines;

      static TickType_t last_flush_time = xTaskGetTickCount();
      if (static_cast<int>(xTaskGetTickCount() - last_flush_time) > pdMS_TO_TICKS(kFlushPeriodMs)) {
        last_flush_time = xTaskGetTickCount();
        const int64_t num_lines = file->num_lines;
        file->Flush();
        UpdateFileTime(filename, NowUnix());
        ESP_LOGD(TAG, "flush at %" PRIi64 " lines", num_lines);
      }  // if flush
    }    // while lines < max
  }      // for split
  ESP_LOGE(TAG, "stopped after making too many (%d) splits", kMaxNumSplits);
}

}  // namespace app