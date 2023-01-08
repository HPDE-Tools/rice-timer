// Copyright (c) rice-timer authors

#include <array>
#include <cstdint>
#include <span>

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "spi.h"

#include "lsm6_reg.h"

static SPI_TypeDef* const kSensorInputSpi = SPI1;
static TIM_TypeDef* const kSensorInputTimer = TIM6;
static TIM_HandleTypeDef* const kSensorInputHTimer = &htim6;

constexpr uint32_t kSensorInputPollFreqHz = 30'000;

constexpr uint32_t kAdcNumChannels = 4;
constexpr uint32_t kAdcMaxNumChannels = 8;
constexpr uint32_t kImuNumChannels = 6;

extern std::array<uint16_t, kAdcMaxNumChannels> g_adc_samples;
extern std::array<int16_t, kImuNumChannels> g_imu_samples;

void SensorInputSetup();
void SensorInputStart();

void SensorInputSendAdcCommand(uint16_t command);
bool SensorInputWriteAdcReg(uint8_t reg, uint8_t value);
uint8_t SensorInputReadAdcReg(uint8_t reg);

void SensorInputWriteImuReg(uint8_t reg, uint8_t value);
uint8_t SensorInputReadImuReg(uint8_t reg);
