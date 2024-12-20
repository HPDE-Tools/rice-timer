
#include <cstdint>
#include <span>

void SpiSetup();

void SpiListen(uint32_t ier, void (*f)(void));

uint8_t SpiRxFifoCount();
uint8_t SpiTxFifoCount();
bool SpiRxEmpty();
bool SpiBusy();
void SpiSetRxFifoWater(uint8_t rxwater);
void SpiSetTxFifoWater(uint8_t txwater);

uint8_t SpiQueueReadAdcData(uint8_t num_channels);
uint8_t SpiQueueReadAdcReg(uint8_t reg);
uint8_t SpiQueueWriteAdcCommand(uint16_t command);
uint8_t SpiQueueWriteAdcReg(uint8_t reg, uint8_t value);

uint8_t SpiQueueReadImuPacked(uint8_t reg, uint8_t num_bytes);
uint8_t SpiQueueWriteImuOne(uint8_t reg, uint8_t value);
bool SpiQueueWriteImuPacked(uint8_t reg, uint8_t num_bytes, std::span<uint32_t> values);

[[nodiscard]] uint32_t SpiWaitReadOne();
void SpiWaitReadPacked(std::span<uint32_t> result);

[[nodiscard]] uint8_t SpiSyncReadAdcReg(uint8_t reg);
void SpiSyncWriteAdcCommand(uint16_t command);
void SpiSyncWriteAdcReg(uint8_t reg, uint8_t value);
[[nodiscard]] uint8_t SpiSyncReadImuOne(uint8_t reg);
bool SpiSyncReadImuPacked(uint8_t reg, uint8_t num_bytes, std::span<uint32_t> result);
void SpiSyncWriteImuOne(uint8_t reg, uint8_t value);