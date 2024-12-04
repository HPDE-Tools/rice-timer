#pragma once

#include <cstdint>

#include "fsl_device_registers.h"

void NeopixelSetupRaw(FLEXIO_Type* f);
bool FlexioTryPush(FLEXIO_Type* f, uint8_t shifter_index, uint32_t data);
