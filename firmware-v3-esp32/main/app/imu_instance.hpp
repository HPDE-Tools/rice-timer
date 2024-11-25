// Copyright 2021 summivox. All rights reserved.
// Authors: summivox@gmail.com

#pragma once

#include <memory>

#include "esp_err.h"

#include "device/imu_driver_lsm6dsr.hpp"

namespace app {

extern std::unique_ptr<Lsm6dsr> g_imu;

esp_err_t SetupImu();
esp_err_t StartImuInstance();

}  // namespace app
