// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <array>
#include <cstdint>

#include "esp_err.h"

namespace app {

/// Statically initialized to the device's "default" base MAC address stored in OTP.
extern const std::array<uint8_t, 6> g_device_mac;

void LogDeviceMac();

/// Make sure the on-chip non-volatile storage is initialized.
esp_err_t NvsInit();

/// Get the device's auto-incrementing "session id" from non-volatile storage
///
/// \return id (>= 0)
///         -1 if fail to access
int64_t NewSessionId();

}  // namespace app
