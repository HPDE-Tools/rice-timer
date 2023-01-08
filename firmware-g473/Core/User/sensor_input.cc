// Copyright (c) rice-timer authors
#include "sensor_input.h"

#include <array>
#include <bit>
#include <atomic>
#include <cstdint>
#include <span>

#include "main.h"
#include "time.h"

#define SPIx kSensorInputSpi
#define TIMx kSensorInputTimer
#define HTIMx kSensorInputHTimer

namespace {

// TODO(summivox): rework
enum class State : uint8_t {
  kIdle,
  kPollingAdc,
  kPollingImu,
};

// std::atomic<uint8_t> g_spi_index = 0;
uint32_t g_spi_index = 0;

volatile int32_t g_debug_total = 0;
volatile uint32_t g_debug_curr = 0;

constexpr uint16_t kAdcDivider = 0b011;
constexpr uint16_t kImuDivider = 0b011;

void SetupSpiForAdc() {
  // CPOL=1, CPHA=0, 16-bit word, RX interrupt
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_MSTR | (kAdcDivider << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b1111 << SPI_CR2_DS_Pos) | SPI_CR2_RXNEIE;
}

void SetupSpiForAdcConfig() {
  // CPOL=1, CPHA=0, 16-bit word
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_MSTR | (kAdcDivider << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b1111 << SPI_CR2_DS_Pos);
}

void SetupSpiForImu() {
  // CPOL=1, CPHA=1, 16-bit word, RX interrupt
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_CPHA | SPI_CR1_MSTR | (kImuDivider << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b1111 << SPI_CR2_DS_Pos) | SPI_CR2_RXNEIE;
}

void SetupSpiForImuConfig() {
  // CPOL=1, CPHA=1, 8-bit word
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_CPHA | SPI_CR1_MSTR | (kImuDivider << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b0111 << SPI_CR2_DS_Pos) | SPI_CR2_FRXTH;
}

void EnableAdc() {  CS_ADC_OUT_GPIO_Port->BSRR = CS_ADC_OUT_Pin << 16; }
void DisableAdc() {  CS_ADC_OUT_GPIO_Port->BSRR = CS_ADC_OUT_Pin; }
void EnableImu() {  CS_IMU_GPIO_Port->BSRR = CS_IMU_Pin << 16; }
void DisableImu() {  CS_IMU_GPIO_Port->BSRR = CS_IMU_Pin; }
void Write16(uint16_t x) { LL_SPI_TransmitData16(SPIx, x); }
uint16_t Read16() { return LL_SPI_ReceiveData16(SPIx); }
void Write8(uint8_t x) { LL_SPI_TransmitData8(SPIx, x); }
uint16_t Read8() { return LL_SPI_ReceiveData8(SPIx); }
bool IsImuIntActive() { return (IMU_INT_GPIO_Port->IDR & IMU_INT_Pin) != 0; }

#if DEBUG_BY_PIN
void Debug1() { LED_GPIO_Port->BSRR = LED_Pin; }
void Debug0() { LED_GPIO_Port->BSRR = LED_Pin << 16; }
#else
void Debug1() {
  g_debug_curr = SysTick->VAL;
}
void Debug0() {
  g_debug_total += static_cast<int32_t>(g_debug_curr - SysTick->VAL);
}
#endif

void TimerHandler(TIM_HandleTypeDef* _htim) __attribute__ ((section(".ccmtext")));
void TimerHandler(TIM_HandleTypeDef* _htim) {
  g_debug_total = 0;  // DEBUG
  Debug1();
  g_spi_index = 0;
  SetupSpiForAdc();
  EnableAdc();
  Write16(0);
  Write16(0);
  Debug0();
}

extern "C" void SensorInputSpiInterrupt() __attribute__ ((section(".ccmtext")));
void SensorInputSpiInterrupt() {
  while (LL_SPI_IsActiveFlag_RXNE(SPIx)) {
    Debug1();
    uint32_t i = g_spi_index++;
    const uint16_t data = Read16();
    // TODO(summivox): dynamic num of channels (specified when starting)
    if (i < kAdcNumChannels * 2) {
      const bool normal = i < (kAdcNumChannels * 2 - 2);
      if (i % 2 == 0) {
      } else {
        DisableAdc();
        g_adc_samples[i / 2] = __builtin_bswap16(data);
        if (normal) {
          // NOTE: This specific ordering balances the following durations without introducing extra delays.
          // - CS rising to CS falling
          // - CS falling to CLK falling
          Write16(0);
          EnableAdc();
          Write16(0);
        } else if (IsImuIntActive()) {
          SetupSpiForImu();
          EnableImu();
          Write16((0x80 | static_cast<uint16_t>(Lsm6Reg::OUT_TEMP_H)) << 8);
          Write16(0);
        }
      }
      Debug0();
      return;
    }
    i -= kAdcNumChannels * 2;
    if (i == 0) {
      Write16(0);
    } else if (i > 0) {
      g_imu_samples[i - 1] = static_cast<int16_t>(__builtin_bswap16(data));
      if (i < kImuNumChannels - 1) {
        Write16(0);
      } else if (i == kImuNumChannels) {
        DisableImu();
      }
    }
    Debug0();
  }
}

}  // namespace

std::array<uint16_t, kAdcMaxNumChannels> g_adc_samples;
std::array<int16_t, kImuNumChannels> g_imu_samples;

void SensorInputSetup() {
  const uint32_t reload = (HAL_RCC_GetPCLK2Freq() << 4) / kSensorInputPollFreqHz;
  TIMx->CR1 &= ~TIM_CR1_CEN;
  TIMx->CR1 |= TIM_CR1_DITHEN;
  TIMx->PSC = 0;
  TIMx->ARR = reload;
  HAL_TIM_RegisterCallback(HTIMx, HAL_TIM_PERIOD_ELAPSED_CB_ID, TimerHandler);

  SetupSpiForAdc();
}

void SensorInputStart() {
  TIM6->CNT = 0;
  HAL_TIM_Base_Start_IT(HTIMx);
}

void SensorInputStop() {
  HAL_TIM_Base_Stop(HTIMx);
}

void SensorInputSendAdcCommand(uint16_t command) {
  SetupSpiForAdcConfig();
  EnableAdc();
  Write16(command);
  Write16(0x0000);
  while (LL_SPI_IsActiveFlag_BSY(SPIx));
  (void)Read16();
  (void)Read16();
  DisableAdc();
}

bool SensorInputWriteAdcReg(uint8_t reg, uint8_t value) {
  SetupSpiForAdcConfig();
  EnableAdc();
  Write16((reg << 9) | 0x0100 | value);
  Write16(0x0000);
  while (LL_SPI_IsActiveFlag_BSY(SPIx));
  const uint16_t data = Read16();
  DisableAdc();
  return value == static_cast<uint8_t>((data >> 8) & 0xFF);
}

uint8_t SensorInputReadAdcReg(uint8_t reg) {
  SetupSpiForAdcConfig();
  EnableAdc();
  Write16(reg << 9);
  Write16(0x0000);
  while (LL_SPI_IsActiveFlag_BSY(SPIx));
  (void)Read16();
  const uint16_t data = Read16();
  DisableAdc();
  return static_cast<uint8_t>((data >> 8) & 0xFF);
}

void SensorInputWriteImuReg(uint8_t reg, uint8_t value) {
  SetupSpiForImuConfig();
  EnableImu();
  Write8(reg);
  Write8(value);
  while (LL_SPI_IsActiveFlag_BSY(SPIx));
  (void)Read8();
  (void)Read8();
  DisableImu();
}

uint8_t SensorInputReadImuReg(uint8_t reg) {
  SetupSpiForImuConfig();
  EnableImu();
  Write8(0x80 | reg);
  Write8(0x00);
  while (LL_SPI_IsActiveFlag_BSY(SPIx));
  (void)Read8();
  const uint8_t result = Read8();
  DisableImu();
  return result;
}
