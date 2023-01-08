// Copyright (c) rice-timer authors
#pragma once

#include "ads8668_reg.h"

void Ads8668Reset();
void Ads8668Scan();
void Ads8668SetRange(uint8_t ch, Ads8668Range range);
void Ads8668SetScannedChannels(uint8_t scanned_channels);
void Ads8668SetEnabledChannels(uint8_t enabled_channels);
