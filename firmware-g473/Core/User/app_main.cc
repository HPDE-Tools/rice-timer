// Copyright (c) rice-timer authors
#include <cstdint>

#include "main.h"
#include "gpio.h"

#include "ads8668.h"
#include "lsm6.h"
#include "sensor_input.h"

extern "C" void app_main() {
  DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM2_STOP | DBGMCU_APB1FZR1_DBG_TIM6_STOP;

  SensorInputSetup();

  Ads8668Reset();
  Ads8668SetEnabledChannels(0b0000'1111);
  Ads8668SetScannedChannels(0b0000'1111);
  Ads8668SetRange(0, Ads8668Range::kBipolar2p5);
  Ads8668SetRange(1, Ads8668Range::kBipolar2p5);
  Ads8668SetRange(2, Ads8668Range::kBipolar2p5);
  Ads8668SetRange(3, Ads8668Range::kBipolar2p5);
  Ads8668Scan();

  Lsm6Configure(
      Lsm6DataRate::kOdr3333Hz,
      Lsm6AccelFullScale::kAccelFs2g,
      Lsm6GyroFullScale::kGyroFs125Dps);

  SensorInputStart();
}
