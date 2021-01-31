#pragma once

#include <cstdint>
#include <memory>

#include "driver/gpio.h"
#include "driver/twai.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc.h"

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

  static std::unique_ptr<CanManager> Create(Option option) {
    auto self = std::unique_ptr<CanManager>(new CanManager(option));
    if (self->Setup() != ESP_OK) {
      self.reset();
    }
    return self;
  }

  virtual ~CanManager();

  esp_err_t Start();
  void Stop();

 protected:
  void Run() override;

 private:
  Option option_;
  explicit CanManager(Option option);

  esp_err_t Setup();
};

// TODO: implement
twai_timing_config_t CalculateCanTiming(int baud_hz, int tseg_1, int tseg_2, int sjw);
