// Copyright (c) rice-timer authors
#include "ads8668.h"

#include "ads8668_reg.h"
#include "sensor_input.h"

void Ads8668Reset() {
  SensorInputSendAdcCommand(static_cast<uint16_t>(Ads8668Command::kRst));
}
void Ads8668Scan() {
  SensorInputSendAdcCommand(static_cast<uint16_t>(Ads8668Command::kAutoRst));
}

void Ads8668SetRange(uint8_t ch, Ads8668Range range) {
  SensorInputWriteAdcReg(Ads8668RangeReg(ch), static_cast<uint8_t>(range));
}
void Ads8668SetScannedChannels(uint8_t scanned_channels) {
  SensorInputWriteAdcReg(static_cast<uint8_t>(Ads8668Reg::kAutoSeqEn), static_cast<uint8_t>(scanned_channels));
}
void Ads8668SetEnabledChannels(uint8_t enabled_channels) {
  SensorInputWriteAdcReg(static_cast<uint8_t>(Ads8668Reg::kChannelPowerDown), static_cast<uint8_t>(~enabled_channels));
}

