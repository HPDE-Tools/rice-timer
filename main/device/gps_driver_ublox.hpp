// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include "esp_err.h"

#include "driver/i2c.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"

#include "io/uart_line_reader.hpp"

esp_err_t SetupUbloxGpsI2c(
    i2c_port_t i2c_num, uint8_t i2c_address_7bit, int desired_baud, int desired_output_period_ms);
