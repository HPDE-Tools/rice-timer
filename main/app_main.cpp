#include "Arduino.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif  // LED_BUILTIN

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);  // set the LED pin mode
  Serial.println("Hello!");
  Serial.println(__cplusplus);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
