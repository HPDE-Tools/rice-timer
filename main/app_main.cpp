#include <inttypes.h>
#include <sys/stat.h>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "driver/spi_common.h"
#include "fmt/chrono.h"
#include "fmt/core.h"
#include "freertos/FreeRTOS.h"
#include "minmea.h"
#include "sdmmc_cmd.h"
#include "soc/uart_struct.h"

#include "capture_manager.hpp"
#include "common/logging.hpp"
#include "common/strings.hpp"
#include "common/utils.hpp"
#include "device/can.hpp"
#include "device/gps_daemon.hpp"
#include "device/gps_driver_mtk.hpp"
#include "device/imu_driver_lsm6dsr.hpp"
#include "filesystem.hpp"
#include "logger.hpp"
#include "ui/model.hpp"
#include "ui/view.hpp"

namespace chrono = std::chrono;

#define HW_VERSION 1

namespace {

constexpr char TAG[] = "main";
constexpr int kI2cMaxFreqHz = 400'000;

#if 0
constexpr int kGpsDesiredBaudRate = HW_VERSION == 1 ? 115200 : HW_VERSION == 2 ? 921600 : 9600;
#endif
constexpr int kGpsDesiredBaudRate = 921600;

constexpr int kGpsDesiredOutputPeriodMs = 100;

constexpr int kCanaryPeriodMs = 10000;

}  // namespace

esp_err_t SetupFileSystem() {
  if (/*CONFIG_SD_CARD_4BIT*/ false) {
    TRY(fs::InitializeSdCard());
  } else {
    TRY(fs::InitializeSdCardSpi());
  }
  return ESP_OK;
}

QueueHandle_t g_gps_uart_queue;
std::unique_ptr<io::UartLineReader> g_gps_line_reader;
std::unique_ptr<GpsDaemon> g_gpsd;

std::unique_ptr<CanManager> g_can;

esp_err_t SetupGps(
    uart_port_t uart_num,
    uart_dev_t* uart_dev,
    gpio_num_t tx_pin,
    gpio_num_t rx_pin,
    gpio_num_t pps_pin) {
  const uart_config_t config{
      .baud_rate = kGpsDesiredBaudRate,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
      .rx_flow_ctrl_thresh = 0,
      .source_clk = UART_SCLK_APB,
  };
  TRY(uart_driver_install(
      uart_num, /*rx buf*/ 1024, /*tx buf*/ 1024, /*queue size*/ 128, &g_gps_uart_queue, 0));
  TRY(uart_param_config(uart_num, &config));
  TRY(uart_set_pin(uart_num, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

  g_gps_line_reader = io::UartLineReader::Create(
      uart_num,
      g_gps_uart_queue,
      {
          .delimiter = '\n',
          .repeat = 1,
      });
  if (!g_gps_line_reader) {
    return ESP_FAIL;
  }

  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, pps_pin));

  g_gpsd = GpsDaemon::Create(
      g_gps_line_reader.get(),
      CaptureManager::GetInstance(MCPWM_UNIT_0),
      // vendor-specific GPS setup handler
      [uart_num, uart_dev](io::UartLineReader* line_reader) -> bool {
        if (HW_VERSION == 1) {
          OK_OR_RETURN(
              SetupMtkGps(
                  uart_num, uart_dev, line_reader, kGpsDesiredBaudRate, kGpsDesiredOutputPeriodMs),
              false);
        }
        // HW v2 GPS is pre-configured and does not need autobaud or config command
        // Using the MTK routine does not hurt though (it should be able to autobaud)
        return true;
      },
      GpsDaemon::Option{
          .pps_capture_signal = MCPWM_SELECT_CAP0,
          .software_capture_signal = MCPWM_SELECT_CAP2,
          .priority = 5,
      });
  if (!g_gpsd) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

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
            auto& g = ui::g_model.gps.emplace();
            g.hour = rmc.time.hours;
            g.minute = rmc.time.minutes;
            g.second = rmc.time.seconds;
            g.millisecond = rmc.time.microseconds / 1000;
            g.latitude = minmea_tocoord(&rmc.latitude);
            g.longitude = minmea_tocoord(&rmc.longitude);
          },
          [](const minmea_sentence_gga& gga) {
            ESP_LOGV(TAG, "parsed GGA: sat=%d", gga.satellites_tracked);
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

TaskHandle_t g_main_task{};
void MainTask(void* /* unused */) {
  vTaskDelay(pdMS_TO_TICKS(2000));  // let monitor connect

  heap_caps_print_heap_info(MALLOC_CAP_8BIT);
  CHECK_OK(SetupFileSystem());

  CHECK_OK(SetupGps(
      UART_NUM_2,
      &UART2,
      /*tx*/ GPIO_NUM_17,
      /*rx*/ GPIO_NUM_16,
      /*pps*/
      (HW_VERSION == 1   ? GPIO_NUM_4
       : HW_VERSION == 2 ? GPIO_NUM_21
                         : GPIO_NUM_NC)));

  g_can = CanManager::Create({
#if HW_VERSION == 1
    .tx_pin = GPIO_NUM_12, .rx_pin = GPIO_NUM_27,
#elif HW_VERSION == 2
    .tx_pin = GPIO_NUM_33, .rx_pin = GPIO_NUM_32,
#endif
    .priority = 3,
  });
  CHECK(g_can);

  CHECK_OK(LoggerInit());

  CHECK_OK(LoggerStart());
  CHECK_OK(g_gpsd->Start(HandleGpsData, HandleGpsLine));
  CHECK_OK(g_can->Start());

  // BEGIN DEBUG
  if (HW_VERSION == 1) {
    gpio_pad_select_gpio(GPIO_NUM_13);
    gpio_set_direction(GPIO_NUM_13, GPIO_MODE_OUTPUT);
    CHECK_OK(SetupLsm6dsrImu({
        .spi = VSPI_HOST,
        .mosi_pin = GPIO_NUM_25,
        .miso_pin = GPIO_NUM_39,
        .sclk_pin = GPIO_NUM_26,
        .cs_pin = GPIO_NUM_21,
        .int1_pin = GPIO_NUM_34,
    }));
  } else if (HW_VERSION == 2) {
    CHECK_OK(SetupLsm6dsrImu({
        .spi = VSPI_HOST,
        .mosi_pin = GPIO_NUM_23,
        .miso_pin = GPIO_NUM_19,
        .sclk_pin = GPIO_NUM_18,
        .cs_pin = GPIO_NUM_5,
        .int1_pin = GPIO_NUM_22,
    }));
  }
  CHECK_OK(TestImu());
  // END DEBUG

  // CHECK_OK(ui::ViewStart());

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
