#pragma once

#include "esp_err.h"

#include "driver/uart.h"
#include "soc/uart_struct.h"

#include "io/uart_line_reader.hpp"

esp_err_t SetupMtkGps(
    uart_port_t uart_num,
    uart_dev_t* uart_dev,
    io::UartLineReader* line_reader,
    int desired_baud,
    int desired_output_period_ms);
