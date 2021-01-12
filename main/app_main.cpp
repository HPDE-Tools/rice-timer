#include "Arduino.h"

#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif  // LED_BUILTIN

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void setup() {
  Serial.begin(115200);
  Wire.begin(23, 22);
  pinMode(LED_BUILTIN, OUTPUT);

  alpha4.begin(0x70);  // pass in the address

  alpha4.writeDigitRaw(3, 0x0);
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(0, 0x0);
  alpha4.writeDigitRaw(1, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(1, 0x0);
  alpha4.writeDigitRaw(2, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(2, 0x0);
  alpha4.writeDigitRaw(3, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);

  alpha4.clear();
  alpha4.writeDisplay();
#if 0
  // display every character,
  for (uint8_t i = '!'; i <= 'z'; i++) {
    alpha4.writeDigitAscii(0, i);
    alpha4.writeDigitAscii(1, i + 1);
    alpha4.writeDigitAscii(2, i + 2);
    alpha4.writeDigitAscii(3, i + 3);
    alpha4.writeDisplay();

    delay(300);
  }
#endif
  Serial.println("Start typing to display!");
}

char displaybuffer[4] = {' ', ' ', ' ', ' '};

void loop() {
  const int level = (millis() / 100) % 10 < 2;
  // digitalWrite(LED_BUILTIN, level);
  gpio_set_level(gpio_num_t(13), level);

  while (!Serial.available()) return;

  char c = Serial.read();
  Serial.write(c);
  if (!isprint(c)) return;  // only printable!

  // scroll down display
  displaybuffer[0] = displaybuffer[1];
  displaybuffer[1] = displaybuffer[2];
  displaybuffer[2] = displaybuffer[3];
  displaybuffer[3] = c;

  // set every digit to the buffer
  alpha4.writeDigitAscii(0, displaybuffer[0]);
  alpha4.writeDigitAscii(1, displaybuffer[1]);
  alpha4.writeDigitAscii(2, displaybuffer[2]);
  alpha4.writeDigitAscii(3, displaybuffer[3]);

  // write it out!
  alpha4.writeDisplay();
  delay(200);
}
