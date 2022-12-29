// Copyright (c) rice-timer authors

#include <array>
#include <bit>
#include <atomic>
#include <cstdint>

#include "main.h"
#include "time.h"

#include "sensor_input.h"

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

#include "lsm6_reg.inl"

__attribute__((always_inline)) void SetupSpiForAdc() {
  // CPOL=1, CPHA=0, 1:8 divider, 16-bit word
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_MSTR | (0b011 << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b1111 << SPI_CR2_DS_Pos) | SPI_CR2_RXNEIE;
}

__attribute__((always_inline)) void SetupSpiForImu() {
  // CPOL=1, CPHA=1, 1:16 divider, 16-bit word
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_CPHA | SPI_CR1_MSTR | (0b011 << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b1111 << SPI_CR2_DS_Pos) | SPI_CR2_RXNEIE;
}

__attribute__((always_inline)) void EnableAdc() {  CS_ADC_OUT_GPIO_Port->BSRR = CS_ADC_OUT_Pin << 16; }
__attribute__((always_inline)) void DisableAdc() {  CS_ADC_OUT_GPIO_Port->BSRR = CS_ADC_OUT_Pin; }
__attribute__((always_inline)) void EnableImu() {  CS_IMU_GPIO_Port->BSRR = CS_IMU_Pin << 16; }
__attribute__((always_inline)) void DisableImu() {  CS_IMU_GPIO_Port->BSRR = CS_IMU_Pin; }
__attribute__((always_inline)) void Write16(uint16_t x) { LL_SPI_TransmitData16(SPIx, x); }
__attribute__((always_inline)) uint16_t Read16() { return LL_SPI_ReceiveData16(SPIx); }

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
        } else {
          SetupSpiForImu();
          EnableImu();
          Write16((0x80 | Lsm6Reg::OUT_TEMP_L) << 8);
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
      g_imu_samples[i - 1] = __builtin_bswap16(data);
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

std::array<uint16_t, kAdcNumChannels> g_adc_samples;
std::array<uint16_t, kImuNumChannels> g_imu_samples;

void SensorInputSetup() {
  const uint32_t reload = (HAL_RCC_GetPCLK2Freq() << 4) / kSensorInputPollFreqHz;
  TIMx->CR1 &= ~TIM_CR1_CEN;
  TIMx->CR1 |= TIM_CR1_DITHEN;
  TIMx->PSC = 0;
  TIMx->ARR = reload;
  HAL_TIM_RegisterCallback(HTIMx, HAL_TIM_PERIOD_ELAPSED_CB_ID, TimerHandler);
}

void SensorInputStart() {
  TIM6->CNT = 0;
  HAL_TIM_Base_Start_IT(HTIMx);
}

void SensorInputStop() {
  HAL_TIM_Base_Stop(HTIMx);
}

