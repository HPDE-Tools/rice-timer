#include "neopixel.hpp"

#include <cassert>
#include <cstdint>

#include "fsl_device_registers.h"


constexpr uint8_t kShifterIndex = 0;
constexpr uint8_t kTimerBaudIndex = 0;
constexpr uint8_t kTimerLowIndex = 1;
constexpr uint8_t kTimerHighIndex = 2;
constexpr uint8_t kOutputPin = 12;
constexpr uint8_t kShifterPin = 0;
constexpr uint8_t kDebugHighBitPin = 1;
constexpr uint8_t kDebugBaudClockPin = 2;

constexpr uint16_t kWidthA = 32;
constexpr uint16_t kWidthB = 68;

constexpr uint8_t kNumBitsPerWord = 24;

constexpr bool kDebugOutputClock = true;

void NeopixelSetupRaw(FLEXIO_Type* f) {
  f->SHIFTCTL[kShifterIndex] = 0u
      | FLEXIO_SHIFTCTL_TIMSEL(kTimerBaudIndex) | FLEXIO_SHIFTCTL_PINCFG(0b11)  // pin = output (REQUIRED, but okay to not map externally)
          | FLEXIO_SHIFTCTL_PINSEL(kShifterPin)
          | FLEXIO_SHIFTCTL_SMOD(0b010)// shifter in transmit mode
          ;
  f->SHIFTCFG[kShifterIndex] = 0u;

  f->TIMCMP[kTimerBaudIndex] = ((kWidthA + kWidthB) / 2 - 1) | ((kNumBitsPerWord * 2 - 1) << 8);
  f->TIMCFG[kTimerBaudIndex] = 0u | FLEXIO_TIMCFG_TIMENA(0b010)  // enable = shifter not empty
      | FLEXIO_TIMCFG_TIMDIS(0b010)  // disable = bits done
      | FLEXIO_TIMCFG_TIMRST(0b000)  // reset = never
      | FLEXIO_TIMCFG_TIMDEC(0b00)  // clock = FlexIO, shift = out
      | FLEXIO_TIMCFG_TIMOUT(0b00)  // out=H on enable (ignore reset)
  ;
  f->TIMCTL[kTimerBaudIndex] = 0u | FLEXIO_TIMCTL_TIMOD(0b01)  // baud-bit mode
      | FLEXIO_TIMCTL_TRGSRC(1)  // trigger is internal
      | FLEXIO_TIMCTL_TRGPOL(1)  // trigger is active low
      | FLEXIO_TIMCTL_TRGSEL((kShifterIndex << 2) | 1)  // trigger = shifter flag
      | FLEXIO_TIMCTL_PINCFG(0b11) * kDebugOutputClock  // pin mode output (DEBUG)
      | FLEXIO_TIMCTL_PINSEL(kDebugBaudClockPin) * kDebugOutputClock;

  f->TIMCMP[kTimerLowIndex] = (kWidthA - 1) | ((kWidthB - 1) << 8);
  f->TIMCFG[kTimerLowIndex] = 0u | FLEXIO_TIMCFG_TIMENA(0b110)  // enable = baud clock rising
      | FLEXIO_TIMCFG_TIMDIS(0b010)  // disable = cycle finished
      | FLEXIO_TIMCFG_TIMRST(0b110)  // reset = baud clock rising
      | FLEXIO_TIMCFG_TIMDEC(0b00)  // clock = FlexIO, shift = out
      | FLEXIO_TIMCFG_TIMOUT(0b10)  // out=H on enable and reset
  ;
  f->TIMCTL[kTimerLowIndex] = 0u | FLEXIO_TIMCTL_TIMOD(0b10)  // PWM high mode
      | FLEXIO_TIMCTL_TRGSRC(1)  // trigger is internal
      | FLEXIO_TIMCTL_TRGSEL((kTimerBaudIndex << 2) | 3)  // trigger = baud clock
      | FLEXIO_TIMCTL_PINCFG(0b11)  // pin mode output
      | FLEXIO_TIMCTL_PINSEL(kOutputPin)
  ;

  f->TIMCMP[kTimerHighIndex] = (kWidthB - 1) | ((kWidthA - 1) << 8);
  f->TIMCFG[kTimerHighIndex] = 0u | FLEXIO_TIMCFG_TIMENA(0b110)  // enable = trigger (data) high
      | FLEXIO_TIMCFG_TIMDIS(0b110)  // disable = trigger (data) falling
      | FLEXIO_TIMCFG_TIMRST(0b111)  // reset = trigger (data) rising/falling
      | FLEXIO_TIMCFG_TIMDEC(0b00)  // clock = FlexIO, shift = out
      | FLEXIO_TIMCFG_TIMOUT(0b10)  // out=H on enable and reset
  ;
  f->TIMCTL[kTimerHighIndex] = 0u | FLEXIO_TIMCTL_TIMOD(0b10)  // PWM high mode
      | FLEXIO_TIMCTL_TRGSRC(1)  // trigger is internal
      | FLEXIO_TIMCTL_TRGSEL(kShifterPin << 1)  // trigger = shifter pin
      | FLEXIO_TIMCTL_PINCFG(0b11)  // pin mode output
      | FLEXIO_TIMCTL_PINSEL(kOutputPin)
  ;
}

bool NeopixelTryPush(FLEXIO_Type* f, uint32_t data) {
  if (!(f->SHIFTSTAT & (1 << kShifterIndex))) {
    return false;
  }
  f->SHIFTBUFBIS[kShifterIndex] = data;
  return true;
}
