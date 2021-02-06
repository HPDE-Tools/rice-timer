// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <optional>

#include "driver/uart.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "soc/uart_struct.h"

namespace io {

struct UartAutoBaudOption {
  uint8_t glitch_filter = 0x08;
  uint32_t min_num_edges = 30;
  TickType_t timeout = portMAX_DELAY;
  TickType_t poll_interval = 1;
};

// assumptions:
// - must be run in RTOS task
// - must have exclusive access to UART
// - UART must have been enabled already

std::optional<int32_t> DetectUartBitWidth(uart_dev_t* uart, const UartAutoBaudOption& option);
std::optional<int32_t> DetectUartBaudRate(uart_dev_t* uart, const UartAutoBaudOption& option);
void SetUartBitWidth(uart_dev_t* uart, int32_t bit_width);
std::optional<uint32_t> GetCurrentUartBaudRate(uart_port_t uart_num);

}  // namespace io
