
#include <cstdint>

#include "FreeRTOS.h"
#include "task.h"

#include "neopixel.hpp"

bool FlexioTryPush(FLEXIO_Type* f, uint8_t shifter_i, uint32_t data) {
  if (f->SHIFTSTAT & (1 << shifter_i)) {
    f->SHIFTBUFBIS[shifter_i] = data;
    return true;
  }
  return false;
}


constexpr size_t kNeopixelStackSize = 0x100;
StackType_t g_neopixel_stack[kNeopixelStackSize];
StaticTask_t g_neopixel_task;
void NeopixelTestTask(void* unused_context) {
  (void) unused_context;

  uint32_t neopixel_data[] = { 0x010101'00u, 0x000000'00u, 0x404040'00u };
  constexpr size_t neopixel_data_n = sizeof(neopixel_data) / sizeof(neopixel_data[0]);

  NeopixelSetupRaw(FLEXIO3);

  FlexioTryPush(FLEXIO3, 0, 0);
  FLEXIO3->CTRL = FLEXIO_CTRL_FLEXEN(1);

  int led_i = 0;
  int iter_i = 0;
  while (1) {
    if (FlexioTryPush(FLEXIO3, 0, neopixel_data[led_i])) {
      if (++led_i == neopixel_data_n) {
        led_i = 0;
        ++iter_i;

        constexpr int period = 1000;
        constexpr int v_max = 50;
        constexpr uint32_t base[] = { 0x000100'00u, 0x010100'00u, 0x010000'00u, 0x010001'00u,
            0x000001'00u, 0x000101'00u, 0x010101'00u, 0x000000'00u, };
        constexpr int base_n = sizeof(base) / sizeof(base[0]);

        int v = iter_i % (v_max * 2);
        v = v >= v_max ? (v_max * 2) - v : v;
        int rotate = (iter_i / (v_max * 2)) % base_n;
        neopixel_data[0] = v * base[(rotate + 0) % base_n];
        neopixel_data[1] = v * base[(rotate + 1) % base_n];
        neopixel_data[2] = v * base[(rotate + 2) % base_n];

        vTaskDelay(period / (v_max * 2));
      }
    }
  }
}

void NeopixelTestTaskInit() {
  xTaskCreateStatic(NeopixelTestTask, "neopixel", kNeopixelStackSize, nullptr, 1, g_neopixel_stack,
                    &g_neopixel_task);
}
