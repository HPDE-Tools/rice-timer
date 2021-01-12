#include "Arduino.h"

#include "Adafruit_BNO055.h"
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"

#include "nameof.hpp"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif  // LED_BUILTIN

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

char displaybuffer[4] = {' ', ' ', ' ', ' '};
void DisplayTask(void* /*unused*/) {
  TickType_t last_wake_time = xTaskGetTickCount();
  while (true) {
    alpha4.writeDigitAscii(0, displaybuffer[0]);
    alpha4.writeDigitAscii(1, displaybuffer[1]);
    alpha4.writeDigitAscii(2, displaybuffer[2]);
    alpha4.writeDigitAscii(3, displaybuffer[3]);
    alpha4.writeDisplay();

    const int level = (millis() / 100) % 10 < 2;
    digitalWrite(LED_BUILTIN, level);

    vTaskDelayUntil(&last_wake_time, 10);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(23, 22);
  pinMode(LED_BUILTIN, OUTPUT);

  alpha4.begin(0x70);

  xTaskCreatePinnedToCore(
      DisplayTask, NAMEOF(DisplayTask).c_str(), 1024, nullptr, 2, nullptr, APP_CPU_NUM);
}

void loop() {
  while (true) {
    displaybuffer[0] = 'a';
    displaybuffer[1] = 'b';
    displaybuffer[2] = 'c';
    displaybuffer[3] = 'd';
    delay(500);
    displaybuffer[0] = ' ';
    displaybuffer[1] = ' ';
    displaybuffer[2] = ' ';
    displaybuffer[3] = ' ';
    delay(500);
  }
}
