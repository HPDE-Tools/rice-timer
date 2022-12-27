// Copyright (c) rice-timer authors

#include <array>
#include <atomic>
#include <cstdint>

#include "main.h"
#include "time.h"

#include "sensor_input.h"

#define POLLING 1
#define ATOMIC 0

#define SPIx kSensorInputSpi
#define TIMx kSensorInputTimer
#define HTIMx kSensorInputHTimer

namespace {

enum class State : uint8_t {
  kIdle,
  kPollingAdc,
  kPollingImu,
};

#include "lsm6_reg.inl"

#if ATOMIC
std::atomic<State> g_sensor_input_state = State::kIdle;
#else
volatile State g_sensor_input_state = State::kIdle;
#endif

int g_adc_current_channel_i = 0;
std::array<uint16_t, kAdcNumChannels> g_adc_samples;

std::array<uint8_t, 12> g_imu_rx_buf = {};

void SetupSpiForAdc() {
  // CPOL=1, CPHA=0, 1:8 divider, 16-bit word
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_MSTR | (0b010 << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b1111 << SPI_CR2_DS_Pos);
  SPIx->CR1 |= SPI_CR1_SPE;
}

void SetupSpiForImu() {
  // CPOL=1, CPHA=1, 1:16 divider, 8-bit word
  SPIx->CR1 = SPI_CR1_CPOL | SPI_CR1_CPHA | SPI_CR1_MSTR | (0b011 << SPI_CR1_BR_Pos) | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE;
  SPIx->CR2 = (0b0111 << SPI_CR2_DS_Pos) | SPI_CR2_FRXTH;
}

void TimerHandler(TIM_HandleTypeDef* _htim) {
#if ATOMIC
  auto expected = State::kIdle;
  if (!g_sensor_input_state.compare_exchange_weak(expected, State::kPollingAdc)) {
    return;
  }
#else
  if (g_sensor_input_state != State::kIdle) {
    return;
  }
  g_sensor_input_state = State::kPollingAdc;
#endif
  g_adc_current_channel_i = 0;

  HAL_StatusTypeDef status;


#if !POLLING
  // TODO(summivox): obsolete
  SetupSpiForAdc();
  HAL_GPIO_WritePin(CS_ADC_OUT_GPIO_Port, CS_ADC_OUT_Pin, GPIO_PIN_RESET);
  status = HAL_SPI_TransmitReceive_IT(
      HSPIx,
      reinterpret_cast<uint8_t*>(g_adc_tx_buf.data()),
      reinterpret_cast<uint8_t*>(g_adc_rx_buf.data()),
      sizeof(g_adc_rx_buf));
  (void)status;
#else
  SetupSpiForAdc();
  for (int i = 0; i < 4; i++) {
    CS_ADC_OUT_GPIO_Port->BSRR = CS_ADC_OUT_Pin << 16;
    LL_SPI_TransmitData16(SPIx, 0x0000);
    LL_SPI_TransmitData16(SPIx, 0x0000);
    while (LL_SPI_IsActiveFlag_BSY(SPIx));
    (void)LL_SPI_ReceiveData16(SPIx);
    g_adc_samples[i] = LL_SPI_ReceiveData16(SPIx);  // TODO(summivox): byte swap
    CS_ADC_OUT_GPIO_Port->BSRR = CS_ADC_OUT_Pin;
    if (i < 3) {
      volatile int y;
      y = 0;
      y = 1;
      y = 2;
      y = 3;
      y = 4;
    }
  }

  if (true || IMU_INT_GPIO_Port->IDR & IMU_INT_Pin) {
    g_sensor_input_state = State::kPollingImu;

    SetupSpiForImu();
    CS_IMU_GPIO_Port->BSRR = CS_IMU_Pin << 16;

    LL_SPI_TransmitData8(SPIx, 0x80 | Lsm6Reg::OUTX_H_G);
    LL_SPI_TransmitData8(SPIx, 0);
    LL_SPI_TransmitData8(SPIx, 0);
    LL_SPI_TransmitData8(SPIx, 0);
    int num_tx_left = 13 - 4;
    int rx_i = 0;
    while (rx_i < 12) {
      if (num_tx_left > 0 && LL_SPI_IsActiveFlag_TXE(SPIx)) {
        LL_SPI_TransmitData8(SPIx, 0);
        --num_tx_left;
      }
      if (LL_SPI_IsActiveFlag_RXNE(SPIx)) {
        g_imu_rx_buf[rx_i++] = LL_SPI_ReceiveData8(SPIx);
      }
    }
    while(LL_SPI_IsActiveFlag_BSY(SPIx));
    CS_IMU_GPIO_Port->BSRR = CS_IMU_Pin;
  }

  g_sensor_input_state = State::kIdle;
#endif  // POLLING
}

#if !POLLING
void SpiCompleteHandler(SPI_HandleTypeDef* _hspi) {
  HAL_StatusTypeDef status;

  State state = g_sensor_input_state;
  switch (state) {
  case State::kPollingAdc: {
    HAL_GPIO_WritePin(CS_ADC_OUT_GPIO_Port, CS_ADC_OUT_Pin, GPIO_PIN_SET);
    g_adc_samples[g_adc_current_channel_i++] = g_adc_rx_buf[1];

    if (g_adc_current_channel_i == kAdcNumChannels) {
      // We have scanned all ADC channels; check if IMU needs polling.
      // TODO(summivox): feed the ADC samples to downstream
      if (true /*HAL_GPIO_ReadPin(IMU_INT_GPIO_Port, IMU_INT_Pin) == GPIO_PIN_SET*/) {
        g_sensor_input_state = State::kPollingImu;

        SetupSpiForImu();
        HAL_GPIO_WritePin(CS_IMU_GPIO_Port, CS_IMU_Pin, GPIO_PIN_RESET);
        status = HAL_SPI_TransmitReceive_DMA(
            HSPIx,
            reinterpret_cast<uint8_t*>(g_imu_tx_buf.data()),
            reinterpret_cast<uint8_t*>(g_imu_rx_buf.data()),
            sizeof(g_imu_rx_buf));
      } else {
        g_sensor_input_state = State::kIdle;
      }
    } else {
      HAL_GPIO_WritePin(CS_ADC_OUT_GPIO_Port, CS_ADC_OUT_Pin, GPIO_PIN_RESET);
      status = HAL_SPI_TransmitReceive_IT(
          HSPIx,
          reinterpret_cast<uint8_t*>(g_adc_tx_buf.data()),
          reinterpret_cast<uint8_t*>(g_adc_rx_buf.data()),
          sizeof(g_adc_rx_buf));
    }
  } break;
  case State::kPollingImu: {
    HAL_GPIO_WritePin(CS_IMU_GPIO_Port, CS_IMU_Pin, GPIO_PIN_SET);
    // TODO(summivox): feed the IMU samples to downstream
    g_sensor_input_state = State::kIdle;
  } break;
  default: break;
  }

  (void)status;
}
#endif

}  // namespace

void SensorInputSetup() {
  const uint32_t reload = (HAL_RCC_GetPCLK2Freq() << 4) / kSensorInputPollFreqHz;
  TIMx->CR1 &= ~TIM_CR1_CEN;
  TIMx->CR1 |= TIM_CR1_DITHEN;
  TIMx->PSC = 0;
  TIMx->ARR = reload;
  HAL_TIM_RegisterCallback(HTIMx, HAL_TIM_PERIOD_ELAPSED_CB_ID, TimerHandler);

#if !POLLING
  HAL_SPI_RegisterCallback(HSPIx, HAL_SPI_TX_RX_COMPLETE_CB_ID, SpiCompleteHandler);
#endif
}

void SensorInputStart() {
  TIM6->CNT = 0;
  HAL_TIM_Base_Start_IT(HTIMx);
}

void SensorInputStop() {
  HAL_TIM_Base_Stop(HTIMx);
}

