// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#include "app/gps_instance.hpp"

#include <memory>

#include "driver/uart.h"
#include "soc/uart_periph.h"

#include "app/shared_i2c_bus.hpp"
#include "common/logging.hpp"
#include "device/gps_driver_mtk.hpp"
#include "device/gps_driver_ublox.hpp"
#include "device/gps_utils.hpp"
#include "io/uart_line_reader.hpp"
#include "priorities.hpp"

namespace app {

namespace {

constexpr int kGpsUartDesiredBaudRate = 921600;
constexpr int kGpsUartRxBufSize = 4096;
constexpr int kGpsUartTxBufSize = 0;
constexpr int kGpsUartQueueSize = 128;

constexpr int kGpsDesiredOutputPeriodMs = 100;

esp_err_t SetupUartPins(uart_port_t uart_num, uart_dev_t* uart_dev) {
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
  TRY(uart_driver_install(
      uart_num, kGpsUartRxBufSize, kGpsUartTxBufSize, kGpsUartQueueSize, &g_gps_uart_queue, 0));
  TRY(uart_param_config(uart_num, &config));
  TRY(uart_set_pin(uart_num, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  TRY(mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM_CAP_0, pps_pin));
  return ESP_OK;
}

}  // namespace

QueueHandle_t g_gps_uart_queue;
std::unique_ptr<io::UartLineReader> g_gps_line_reader;
std::unique_ptr<GpsDaemon> g_gpsd;

esp_err_t SetupGps() {
  TRY(SetupSharedI2cBus());

  const uart_port_t uart_num = UART_NUM_2;
  uart_dev_t* const uart_dev = &UART2;
  TRY(SetupUartPins(uart_num, uart_dev));

  g_gps_line_reader = io::UartLineReader::Create(
      uart_num,
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
      // vendor-specific GPS setup handler
      [uart_num, uart_dev](io::UartLineReader* line_reader) -> bool {
        if constexpr (CONFIG_HW_VERSION == 1) {
          OK_OR_RETURN(
              SetupMtkGps(
                  uart_num,
                  uart_dev,
                  line_reader,
                  kGpsUartDesiredBaudRate,
                  kGpsDesiredOutputPeriodMs),
              false);
        } else if constexpr (2 <= CONFIG_HW_VERSION && CONFIG_HW_VERSION <= 3) {
          OK_OR_RETURN(
              SetupUbloxGpsI2c(
                  I2C_NUM_0,
                  /*7-bit address*/ 0x42,
                  kGpsUartDesiredBaudRate,
                  kGpsDesiredOutputPeriodMs),
              false);
        }
        return true;
      },
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

}  // namespace app
