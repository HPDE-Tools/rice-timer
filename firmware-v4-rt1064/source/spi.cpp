#include "spi.hpp"

#include <cstdint>
#include <span>

#include "fsl_device_registers.h"
#include "fsl_lpspi.h"

#include "utils.hpp"

LPSPI_Type* const SPI = LPSPI4;

void SpiSetup() {
#if 0
  // enable and reset
  CCM_CCGR1 = CCM_CCGR1 | CCM_CCGR1_LPSPI4(0b11);
  SPI->CR = LPSPI_CR_MEN | LPSPI_CR_RST | LPSPI_CR_RTF | LPSPI_CR_RRF;
  SPI->CR = LPSPI_CR_MEN;

  // pinout
  // - PCS0=B0_00(#10), PCS1=B1_03(#37), PCS2=B1_02(#36)
  // - SCK=B0_03(#13), MOSI=B0_02(#11), MISO=B0_01(#12)
  
  // PCS0 = B0_00
  IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00 = 3;
  IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00 = IOMUXC_PAD_DSE(0b100) /* strength R0/4 */;
  IOMUXC_LPSPI4_PCS0_SELECT_INPUT = 0;

  // PCS1 = B1_03
  IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_03 = 2;
  IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_03 = IOMUXC_PAD_DSE(0b100) /* strength R0/4 */;

  // SCK = B0_03
  IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 3;
  IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(0b100) /* strength R0/4 */;
  IOMUXC_LPSPI4_SCK_SELECT_INPUT = 0;

  // MOSI = B0_02
  IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02 = 3;
  IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02 = IOMUXC_PAD_DSE(0b100) /* strength R0/4 */;
  IOMUXC_LPSPI4_SDO_SELECT_INPUT = 0;

  // MISO = B0_01
  IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01 = 3;
  IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01 = IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(0b10);  // DEBUG
  IOMUXC_LPSPI4_SDO_SELECT_INPUT = 0;

  // clock tree
  CCM_CBCMR = CCM_CBCMR
    & ~(CCM_CBCMR_LPSPI_CLK_SEL_MASK | CCM_CBCMR_LPSPI_PODF_MASK)
    | CCM_CBCMR_LPSPI_CLK_SEL(0b10) /* PLL2 = 528 MHz */
    // | CCM_CBCMR_LPSPI_PODF(3 - 1) /* div 3 => 176 MHz = 5.68 ns */
    ;
#endif

  SPI->CCR = 0u
    | LPSPI_CCR_SCKDIV(33 - 2) /* SCK period */
    | LPSPI_CCR_DBT(48 - 2) /* delay between transfers */
    | LPSPI_CCR_PCSSCK(24 - 1) /* PCS to first SCK delay */
    | LPSPI_CCR_SCKPCS(24 - 1) /* last SCK to PCS delay */
    ;
  
  // simple master mode
  SPI->CFGR1 = LPSPI_CFGR1_MASTER(1);
}

void SpiListen(uint32_t ier, void (*f)(void)) {
  SPI->IER = ier;
  /*
  attachInterruptVector(IRQ_LPSPI4, f);
  NVIC_ENABLE_IRQ(IRQ_LPSPI4);
  */
}

constexpr uint32_t kAdcCommon = 0u
  | LPSPI_TCR_CPOL(1)
  | LPSPI_TCR_CPHA(0)
  // | LPSPI_TCR_PRESCALE(0b000)
  | LPSPI_TCR_PRESCALE(0b100)
  | LPSPI_TCR_PCS(1)
  ;
constexpr uint32_t kImuCommon = 0u
  | LPSPI_TCR_CPOL(1)
  | LPSPI_TCR_CPHA(1)
  // | LPSPI_TCR_PRESCALE(0b001)
  | LPSPI_TCR_PRESCALE(0b101)
  | LPSPI_TCR_PCS(0)
  ;

uint8_t SpiRxFifoCount() {
  return (SPI->FSR >> 16) & 0b11111;
}
uint8_t SpiTxFifoCount() {
  return SPI->FSR & 0b11111;
}
bool SpiRxEmpty() {
  return SPI->RSR & LPSPI_RSR_RXEMPTY_MASK;
}
bool SpiBusy() {
  return SPI->SR & LPSPI_SR_MBF_MASK;
}
void SpiSetRxFifoWater(uint8_t rxwater) {
  SPI->FCR = ((rxwater & 0xF) << 16) | (SPI->FCR & 0xF);
}
void SpiSetTxFifoWater(uint8_t txwater) {
  SPI->FCR = (SPI->FCR & 0xF0000) | (txwater & 0xF);
}

/// Returns the number of words to be expected in the RX FIFO.
uint8_t SpiQueueReadAdcData(uint8_t num_channels) {
  SPI->TCR = kAdcCommon
    | LPSPI_TCR_FRAMESZ(32 - 1)
    ;
  for (int i = 0; i < num_channels; ++i) {
    SPI->TDR = i < (num_channels - 1) ? 0x0000'0000 : 0xA000'0000;
  }
  return num_channels;
}

uint8_t SpiQueueReadAdcReg(uint8_t reg) {
  SPI->TCR = kAdcCommon
    | LPSPI_TCR_FRAMESZ(32 - 1)
    ;
  SPI->TDR = uint32_t{reg} << 25;
  return 1;
}

/// Returns the number of words to be expected in the RX FIFO.
uint8_t SpiQueueWriteAdcCommand(uint16_t command) {
  SPI->TCR = kAdcCommon
    | LPSPI_TCR_FRAMESZ(32 - 1)
    ;
  SPI->TDR = uint32_t{command} << 16;
  return 1;
}

/// Returns the number of words to be expected in the RX FIFO.
uint8_t SpiQueueWriteAdcReg(uint8_t reg, uint8_t value) {
  SPI->TCR = kAdcCommon
    | LPSPI_TCR_FRAMESZ(32 - 1)
    ;
  SPI->TDR = ((uint32_t{reg} << 9) | 0x0100 | value) << 16;
  return 1;
}

uint8_t SpiQueueReadImuOne(uint8_t reg) {
  SPI->TCR = kImuCommon
    | LPSPI_TCR_FRAMESZ(16 - 1)
    ;
  SPI->TDR = (0x80 | uint32_t{reg}) << 8;
  return 1;
}

/// Returns the number of words to be expected in the RX FIFO.
uint8_t SpiQueueReadImuPacked(uint8_t reg, uint8_t num_bytes) {
  SPI->TCR = kImuCommon
    | LPSPI_TCR_CONT(1)
    | LPSPI_TCR_RXMSK(1)
    | LPSPI_TCR_FRAMESZ(8 - 1)
    ;
  SPI->TDR = 0x80 | reg;
  SPI->TCR = kImuCommon
    | LPSPI_TCR_CONTC(1)
    | LPSPI_TCR_TXMSK(1)
    | LPSPI_TCR_FRAMESZ(uint16_t{num_bytes} * 8 - 1)
    ;
  return (num_bytes + 3) / 4;
}

/// Returns the number of words to be expected in the RX FIFO.
uint8_t SpiQueueWriteImuOne(uint8_t reg, uint8_t value) {
  SPI->TCR = kImuCommon
    | LPSPI_TCR_FRAMESZ(16 - 1)
    ;
  SPI->TDR = (uint32_t{reg} << 8) | value;
  return 1;
}

bool SpiQueueWriteImuPacked(uint8_t reg, uint8_t num_bytes, std::span<uint32_t> values) {
  const size_t num_words = (num_bytes + 3) / 4;
  if (values.size() != num_words) {
    return false;
  }
  SPI->TCR = kImuCommon
    | LPSPI_TCR_CONT(1)
    | LPSPI_TCR_RXMSK(1)
    | LPSPI_TCR_FRAMESZ(8 - 1)
    ;
  SPI->TDR = reg;
  SPI->TCR = kImuCommon
    | LPSPI_TCR_CONTC(1)
    | LPSPI_TCR_FRAMESZ(uint16_t{num_bytes} * 8 - 1)
    ;
  for (const uint32_t value : values) {
    while (SpiTxFifoCount() >= 0b11111) ;
    SPI->TDR = value;
  }
  return true;
}

/// Returns the word read.
[[nodiscard]] uint32_t SpiWaitReadOne() {
  while (SpiRxEmpty()) ;
  return SPI->RDR;
}

void SpiWaitReadPacked(std::span<uint32_t> result) {
  for (size_t i = 0; i < result.size(); ++i) {
    result[i] = SpiWaitReadOne();
  }
}

[[nodiscard]] uint8_t SpiSyncReadAdcReg(uint8_t reg) {
  while (SpiBusy()) ;
  SpiQueueReadAdcReg(reg);
  return SpiWaitReadOne();
}

void SpiSyncWriteAdcCommand(uint16_t command) {
  while (SpiBusy()) ;
  SpiQueueWriteAdcCommand(command);
  (void)SpiWaitReadOne();
}

void SpiSyncWriteAdcReg(uint8_t reg, uint8_t value) {
  while (SpiBusy()) ;
  SpiQueueWriteAdcReg(reg, value);
  (void)SpiWaitReadOne();
}

[[nodiscard]] uint8_t SpiSyncReadImuOne(uint8_t reg) {
  while (SpiBusy()) ;
  SpiQueueReadImuOne(reg);
  return SpiWaitReadOne();
}

bool SpiSyncReadImuPacked(uint8_t reg, uint8_t num_bytes, std::span<uint32_t> result) {
  if (result.size() * 4 < num_bytes) {
    return false;
  }
  while (SpiBusy()) ;
  SpiQueueReadImuPacked(reg, num_bytes);
  SpiWaitReadPacked(result);
  return true;
}

void SpiSyncWriteImuOne(uint8_t reg, uint8_t value) {
  while (SpiBusy()) ;
  SpiQueueWriteImuOne(reg, value);
  (void)SpiWaitReadOne();
}
