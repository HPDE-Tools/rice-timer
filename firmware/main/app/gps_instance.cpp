// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/gps_instance.hpp"

#include <memory>

#include "driver/uart.h"
#include "soc/uart_periph.h"

#include "app/logger_instance.hpp"
#include "app/shared_i2c_bus.hpp"
#include "common/macros.hpp"
#include "common/strings.hpp"
#include "device/gps_driver_mtk.hpp"
#include "device/gps_driver_ublox.hpp"
#include "device/gps_utils.hpp"
#include "io/uart_line_reader.hpp"
#include "priorities.hpp"
#include "ui/model.hpp"

namespace app {

namespace {

constexpr char TAG[] = "app/gps";

constexpr int kGpsUartDesiredBaudRate = 921600;
constexpr int kGpsUartRxBufSize = 4096;
constexpr int kGpsUartTxBufSize = 0;
constexpr int kGpsUartQueueSize = 128;

constexpr int kGpsDesiredOutputPeriodMs = 100;

const uart_port_t kGpsUartNum = UART_NUM_2;
uart_dev_t* const g_gps_uart_dev = &UART2;

esp_err_t SetupUartPins() {
  gpio_num_t tx_pin = GPIO_NUM_NC;
  gpio_num_t rx_pin = GPIO_NUM_NC;
  gpio_num_t pps_pin = GPIO_NUM_NC;
  if constexpr (CONFIG_HW_VERSION == 1) {
    tx_pin = GPIO_NUM_17;
    rx_pin = GPIO_NUM_16;
    pps_pin = GPIO_NUM_4;
  } else if constexpr (CONFIG_HW_VERSION == 2) {
    tx_pin = GPIO_NUM_17;
    rx_pin = GPIO_NUM_16;
    pps_pin = GPIO_NUM_21;
  } else if constexpr (CONFIG_HW_VERSION == 3) {
    tx_pin = GPIO_NUM_27;
    rx_pin = GPIO_NUM_26;
    pps_pin = GPIO_NUM_25;
  } else {
    return ESP_ERR_NOT_SUPPORTED;
  }

  const uart_config_t config{
      .baud_rate = kGpsUartDesiredBaudRate,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
      .rx_flow_ctrl_thresh = 0,
      .source_clk = UART_SCLK_APB,
  };
  const int flags = CONFIG_UART_ISR_IN_IRAM ? ESP_INTR_FLAG_IRAM : 0;
  TRY(uart_driver_install(
      kGpsUartNum,
      kGpsUartRxBufSize,
      kGpsUartTxBufSize,
      kGpsUartQueueSize,
      &g_gps_uart_queue,
      flags));
  TRY(uart_param_config(kGpsUartNum, &config));
  TRY(uart_set_pin(kGpsUartNum, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, pps_pin));
  return ESP_OK;
}

bool GpsDeviceSetup(io::UartLineReader* line_reader) {
  if constexpr (CONFIG_HW_VERSION == 1) {
    OK_OR_RETURN(
        SetupMtkGps(
            kGpsUartNum,
            g_gps_uart_dev,
            line_reader,
            kGpsUartDesiredBaudRate,
            kGpsDesiredOutputPeriodMs),
        false);
  } else if constexpr (2 <= CONFIG_HW_VERSION && CONFIG_HW_VERSION <= 3) {
    // DEBUG: don't do I2C
#if 1
    OK_OR_RETURN(
        SetupUbloxGpsI2c(
            I2C_NUM_0,
            /*7-bit address*/ 0x42,
            kGpsUartDesiredBaudRate,
            kGpsDesiredOutputPeriodMs),
        false);
#endif
  }
  return true;
}

void HandleGpsStateChange(GpsDaemon::State state) {
  ESP_LOGI(TAG, "gps state change -> %d", state);
  if (state != GpsDaemon::kActive) {
    ui::g_model.gps.reset();
  }
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
            if (rmc.valid) {
              if (!ui::g_model.gps) {
                ui::g_model.gps.emplace();
              }
              auto& g = *ui::g_model.gps;
              g.year = rmc.date.year + kBuildCentury;
              g.month = rmc.date.month;
              g.day = rmc.date.day;
              g.hour = rmc.time.hours;
              g.minute = rmc.time.minutes;
              g.second = rmc.time.seconds;
              g.millisecond = rmc.time.microseconds / 1000;
              g.latitude = minmea_tocoord(&rmc.latitude);
              g.longitude = minmea_tocoord(&rmc.longitude);
              g.speed_knot = minmea_tofloat(&rmc.speed);
              g.course_deg = minmea_tofloat(&rmc.course);
              ++ui::g_model.counter.gps;
              // OnboardAnalysisUpdateGps(rmc);  // TODO: track timer
            }
          },
          [](const minmea_sentence_gga& gga) {
            ESP_LOGV(TAG, "parsed GGA: sat=%d", gga.satellites_tracked);
            if (ui::g_model.gps) {
              ui::g_model.gps->num_sats = gga.satellites_tracked;
            }
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
    const esp_err_t err = SendToLogger(
        app::kGpsProducer,
        fmt::format("p,{},{}", time_fix->pps_capture, time_fix->parsed_time_unix));
    if (err == ESP_FAIL) {
      ++ui::g_model.lost.gps;
    }
  }
}

void HandleGpsLine(std::string_view line, bool is_valid_nmea) {
  static const CaptureChannel channel =
      CaptureManager::GetInstance(MCPWM_UNIT_0)->GetChannel(MCPWM_SELECT_CAP2);

  const std::string_view trimmed = TrimSuffix(line, "\r\n");
  ESP_LOGV(TAG, "gps line (valid=%d):%.*s", (int)is_valid_nmea, trimmed.size(), trimmed.data());
  if (is_valid_nmea) {
    const uint32_t capture = channel.TriggerNow();
    const esp_err_t err = SendToLogger(app::kGpsProducer, fmt::format("g,{},{}", capture, trimmed));
    if (err == ESP_FAIL) {
      ++ui::g_model.lost.gps;
    }
  }
}

}  // namespace

QueueHandle_t g_gps_uart_queue{};
std::unique_ptr<io::UartLineReader> g_gps_line_reader{};
std::unique_ptr<GpsDaemon> g_gpsd{};

esp_err_t SetupGps() {
  TRY(SetupSharedI2cBus());
  TRY(SetupUartPins());

  g_gps_line_reader = io::UartLineReader::Create(
      kGpsUartNum,
      g_gps_uart_queue,
      {
          .delimiter = '\n',
          .repeat = 1,

          // NOTE(summivox): queue size increased due to buffer full events observed in the wild
          .queue_size = 64,
      });
  if (!g_gps_line_reader) {
    return ESP_FAIL;
  }

  g_gpsd = GpsDaemon::Create(
      g_gps_line_reader.get(),
      CaptureManager::GetInstance(MCPWM_UNIT_0),
      GpsDaemon::Option{
          .pps_capture_signal = MCPWM_SELECT_CAP0,
          .software_capture_signal = MCPWM_SELECT_CAP2,
          .priority = kPriorityGpsd,
      });
  if (!g_gpsd) {
    return ESP_FAIL;
  }
  return ESP_OK;
}

esp_err_t StartGpsInstance() {
  if (!g_gpsd) {
    return ESP_ERR_INVALID_STATE;
  }
  return g_gpsd->Start(GpsDeviceSetup, HandleGpsStateChange, HandleGpsData, HandleGpsLine);
}

}  // namespace app
