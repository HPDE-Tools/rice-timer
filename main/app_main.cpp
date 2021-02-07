// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include <inttypes.h>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "driver/gpio.h"
#include "fmt/chrono.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "minmea.h"
#include "sdmmc_cmd.h"

#include "app/can_instance.hpp"
#include "app/gps_instance.hpp"
#include "app/imu_instance.hpp"
#include "app/logger.hpp"
#include "app/sd_card_instance.hpp"
#include "common/logging.hpp"
#include "common/strings.hpp"
#include "common/utils.hpp"
#include "ui/model.hpp"
#include "ui/view.hpp"

namespace {

constexpr char TAG[] = "main";

constexpr int kCanaryPeriodMs = 10000;

}  // namespace

using namespace app;  // TODO: move this file altogether

void HandleGpsData(
    GpsDaemon::State state, const ParsedNmea& nmea, const std::optional<GpsTimeFix>& time_fix) {
  ESP_LOGV(
      TAG,
      "gps data: state=%d, nmea=#%d, has_time_fix=%d",
      (int)state,
      (int)nmea.index(),
      (int)!!time_fix);
  std::visit(
      overloaded{
          [](const minmea_sentence_rmc& rmc) {
            ESP_LOGV(
                TAG,
                "parsed RMC: (%+10.6f, %+11.6f)",
                (double)minmea_tocoord(&rmc.latitude),
                (double)minmea_tocoord(&rmc.longitude));
            if (rmc.valid) {
              auto& g = ui::g_model.gps.emplace();
              g.hour = rmc.time.hours;
              g.minute = rmc.time.minutes;
              g.second = rmc.time.seconds;
              g.millisecond = rmc.time.microseconds / 1000;
              g.latitude = minmea_tocoord(&rmc.latitude);
              g.longitude = minmea_tocoord(&rmc.longitude);
            }
          },
          [](const minmea_sentence_gga& gga) {
            ESP_LOGV(TAG, "parsed GGA: sat=%d", gga.satellites_tracked);
          },
          [](const minmea_sentence_gst& gst) {
            ESP_LOGV(
                TAG,
                "parsed GST: lat=%f, long=%f",
                (double)minmea_tofloat(&gst.latitude_error_deviation),
                (double)minmea_tofloat(&gst.longitude_error_deviation));
          },
          [](const auto&) { /* default NOP */ }},
      nmea);
  if (time_fix) {
    SendToLogger(fmt::format("p,{},{}", time_fix->pps_capture, time_fix->parsed_time_unix));
  }
}

void HandleGpsLine(std::string_view line, bool is_valid_nmea) {
  static const CaptureChannel channel =
      CaptureManager::GetInstance(MCPWM_UNIT_0)->GetChannel(MCPWM_SELECT_CAP2);

  const std::string_view trimmed = TrimSuffix(line, "\r\n");
  ESP_LOGV(TAG, "gps line (valid=%d):%.*s", (int)is_valid_nmea, trimmed.size(), trimmed.data());
  if (is_valid_nmea) {
    const uint32_t capture = channel.TriggerNow();
    SendToLogger(fmt::format("g,{},{}", capture, trimmed));
  }
}

void HandleImuRawData(const Lsm6dsr::RawImuData& data) {
  ui::g_model.imu = ui::Model::Imu{
      .ax = data.ax * float{2.0f / 32767},
      .ay = data.ay * float{2.0f / 32767},
      .az = data.az * float{2.0f / 32767},
  };
  SendToLogger(std::move(fmt::format(
      "i,{},{:+06d},{:+06d},{:+06d},{:+06d},{:+06d},{:+06d}",
      data.capture,
      data.ax,
      data.ay,
      data.az,
      data.wx,
      data.wy,
      data.wz)));
}

void HandleSdCardStateChange(bool mounted) {
  if (mounted) {
    sdmmc_card_print_info(stdout, g_sd_card->sd_card());
    ESP_LOGI(TAG, "card mounted; starting logger");
    LoggerStart();
  } else {
    LoggerStop();
    ESP_LOGI(TAG, "card unmounted; logger stopped");
  }
}

TaskHandle_t g_main_task{};
void MainTask(void* /* unused */) {
  ESP_LOGI(TAG, "MainTask started");
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
  vTaskDelay(pdMS_TO_TICKS(2000));

  CHECK_OK(SetupSdCard());
  CHECK_OK(SetupGps());
  CHECK_OK(SetupCan());
  CHECK_OK(SetupImu());
  CHECK_OK(LoggerInit());
  CHECK_OK(ui::ViewInit());

  ESP_LOGI(TAG, "MainTask setup complete");
  heap_caps_print_heap_info(MALLOC_CAP_8BIT);

  CHECK_OK(g_sd_card->Start(HandleSdCardStateChange));
  CHECK_OK(g_gpsd->Start(HandleGpsData, HandleGpsLine));
  CHECK_OK(g_can->Start());
  CHECK_OK(g_imu->Start(HandleImuRawData));
  CHECK_OK(ui::ViewStart());

  vTaskDelete(nullptr);
}

#define LOG_WATER_MARK(name, task) \
  ESP_LOGI("canary", name ": %d", (task) ? uxTaskGetStackHighWaterMark((task)) : -1)

TaskHandle_t g_canary_task{};
void CanaryTask(void* /*unused*/) {
  TickType_t last_wake_tick = xTaskGetTickCount();
  while (true) {
    LOG_WATER_MARK("canary", g_canary_task);
    LOG_WATER_MARK("logger", g_logger_task);
    if (g_gpsd) {
      LOG_WATER_MARK("gpsd", g_gpsd->handle());
    }
    if (g_can) {
      LOG_WATER_MARK("can", g_can->handle());
    }
    if (g_sd_card) {
      LOG_WATER_MARK("sd", g_sd_card->handle());
    }
    LOG_WATER_MARK("ui/view", ui::g_view_task);
    vTaskDelayUntil(&last_wake_tick, pdMS_TO_TICKS(kCanaryPeriodMs));
  }
}

extern "C" void app_main(void) {
  xTaskCreatePinnedToCore(
      CanaryTask,
      "canary",
      2500,
      /*arg*/ nullptr,
      configMAX_PRIORITIES - 2,
      &g_canary_task,
      PRO_CPU_NUM);
  xTaskCreatePinnedToCore(
      MainTask, "main", 4096, /*arg*/ nullptr, configMAX_PRIORITIES - 1, &g_main_task, APP_CPU_NUM);
}
