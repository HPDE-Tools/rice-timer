// Copyright (c) rice-timer authors

#include <array>
#include <cstdint>

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "spi.h"

static SPI_TypeDef* const kSensorInputSpi = SPI1;
static TIM_TypeDef* const kSensorInputTimer = TIM6;
static TIM_HandleTypeDef* const kSensorInputHTimer = &htim6;

constexpr uint32_t kSensorInputPollFreqHz = 30'000;

constexpr uint32_t kAdcNumChannels = 4;
constexpr uint32_t kImuNumChannels = 6;

extern std::array<uint16_t, kAdcNumChannels> g_adc_samples;
extern std::array<uint16_t, kImuNumChannels> g_imu_samples;

void SensorInputSetup();
void SensorInputStart();
