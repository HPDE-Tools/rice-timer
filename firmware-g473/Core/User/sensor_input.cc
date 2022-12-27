// Copyright (c) rice-timer authors

#include <array>
#include <atomic>
#include <cstdint>

#include "main.h"
#include "time.h"

#include "sensor_input.h"

#define POLLING 0
#define ATOMIC 0

#define SPIx kSensorInputSpi
#define HSPIx kSensorInputHSpi
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

std::array<uint8_t, 4> g_adc_tx_buf = {};
std::array<uint8_t, 4> g_adc_rx_buf = {};

std::array<uint8_t, 13> g_imu_tx_buf = {Lsm6Reg::OUTX_H_G};
std::array<uint8_t, 13> g_imu_rx_buf = {};

void SetupSpiForAdc() {
  // CPOL=1, CPHA=0
  SPIx->CR1 = (SPIx->CR1 | SPI_CR1_CPOL) & ~SPI_CR1_CPHA;
}

void SetupSpiForImu() {
  // CPOL=1, CPHA=1
  SPIx->CR1 = SPIx->CR1 | SPI_CR1_CPOL | SPI_CR1_CPHA;
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
    HAL_GPIO_WritePin(CS_ADC_OUT_GPIO_Port, CS_ADC_OUT_Pin, GPIO_PIN_RESET);
    status = HAL_SPI_TransmitReceive(
        HSPIx,
        g_adc_tx_buf.data(),
        g_adc_rx_buf.data(),
        g_adc_rx_buf.size(),
        /*timeout=*/ 1);
    HAL_GPIO_WritePin(CS_ADC_OUT_GPIO_Port, CS_ADC_OUT_Pin, GPIO_PIN_SET);
    g_adc_samples[i] = g_adc_rx_buf[1];
  }
  if (true /*HAL_GPIO_ReadPin(IMU_INT_GPIO_Port, IMU_INT_Pin) == GPIO_PIN_SET*/) {
    g_sensor_input_state = State::kPollingImu;

    SetupSpiForImu();
    HAL_GPIO_WritePin(CS_IMU_GPIO_Port, CS_IMU_Pin, GPIO_PIN_RESET);
    status = HAL_SPI_TransmitReceive(
        HSPIx,
        g_imu_tx_buf.data(),
        g_imu_rx_buf.data(),
        g_imu_rx_buf.size(),
        /*timeout=*/1);
    HAL_GPIO_WritePin(CS_IMU_GPIO_Port, CS_IMU_Pin, GPIO_PIN_SET);
  }
  g_sensor_input_state = State::kIdle;
#endif
}

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

