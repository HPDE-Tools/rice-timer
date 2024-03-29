// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "driver/gpio.h"
#include "driver/twai.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc.h"

#include "common/macros.hpp"
#include "common/task.hpp"

class CanManager : public Task {
 public:
  struct Option {
    gpio_num_t tx_pin = GPIO_NUM_NC;
    gpio_num_t rx_pin = GPIO_NUM_NC;
    uint32_t tx_queue_len = 16;
    uint32_t rx_queue_len = 16;
    twai_mode_t mode = TWAI_MODE_NORMAL;
    twai_timing_config_t timing = TWAI_TIMING_CONFIG_500KBITS();

    int priority = 0;
  };

  using CanMessageSubscriber =
      std::function<void(uint32_t current_capture, const twai_message_t& message)>;

  virtual ~CanManager();

  esp_err_t Start(CanMessageSubscriber subscriber);
  void Stop();

  DEFINE_CREATE(CanManager)

 protected:
  void Run() override;

 private:
  Option option_;
  CanMessageSubscriber subscriber_{};

  explicit CanManager(Option option);

  esp_err_t Setup();
};

/// Wrapper for calculating CAN baud rate prescaler.
/// This does NOT check the validity of the generated timing config --- the driver will anyway.
/// @see twai_timing_config_t for meaning of arguments.
///
constexpr twai_timing_config_t CalculateCanTiming(
    int baud_hz, uint8_t tseg_1, uint8_t tseg_2, uint8_t sjw, bool triple_sampling = false) {
  const uint8_t t_total = 1 + tseg_1 + tseg_2;
  const int denominator = t_total * baud_hz;
  const int prescaler = APB_CLK_FREQ / denominator;

  return twai_timing_config_t{
      .brp = uint32_t(prescaler),
      .tseg_1 = tseg_1,
      .tseg_2 = tseg_2,
      .sjw = sjw,
      .triple_sampling = triple_sampling,
  };
}
