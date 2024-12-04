#pragma once

#include <cstdint>
#include <memory>

#include "fsl_common.h"

constexpr size_t kSdramNumBytes = 32 * 1024 * 1024;
void* const kSdramBase = reinterpret_cast<void*>(0x80000000);

status_t SdramInit(void);
