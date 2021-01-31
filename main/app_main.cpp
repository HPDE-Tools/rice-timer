#include <inttypes.h>
#include <sys/stat.h>
#include <chrono>
#include <memory>
#include <optional>
#include <string>

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
#include "common/utils.hpp"
#include "device/can.hpp"
#include "device/gps_daemon.hpp"
#include "device/gps_driver_mtk.hpp"
#include "filesystem.hpp"
#include "logger.hpp"
#include "ui/view.hpp"

namespace chrono = std::chrono;

#define HW_VERSION 1

namespace {

constexpr char TAG[] = "main";
constexpr int kI2cMaxFreqHz = 400'000;
constexpr int kGpsDesiredBaudRate = 115200;
constexpr int kGpsDesiredOutputPeriodMs = 100;
constexpr int kGpsOutputPeriodMs = 200;

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
        OK_OR_RETURN(
            SetupMtkGps(
                uart_num, uart_dev, line_reader, kGpsDesiredBaudRate, kGpsDesiredOutputPeriodMs),
            false);
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
    GpsDaemon::State state,
    const ParsedNmea& nmea,
    const std::optional<GpsDaemon::TimeFix>& time_fix) {
  ESP_LOGI(
      TAG,
      "gps data handler: state=%d, nmea=#%d, has_time_fix=#%d",
      (int)state,
      (int)nmea.index(),
      (int)!!time_fix);
  std::visit(
      overloaded{
          [](const minmea_sentence_rmc& rmc) {
            ESP_LOGI(
                TAG,
                "parsed RMC: (%+10.6f, %+11.6f)",
                (double)minmea_tocoord(&rmc.latitude),
                (double)minmea_tocoord(&rmc.longitude));
          },
          [](const minmea_sentence_gga& gga) {
            ESP_LOGI(TAG, "parsed GGA: sat=%d", gga.satellites_tracked);
          },
          [](const auto&) { /* default NOP */ }},
      nmea);
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
  CHECK_OK(g_gpsd->Start(HandleGpsData));
  CHECK_OK(g_can->Start());

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
