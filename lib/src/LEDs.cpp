#include "../inc/LEDs.h"
#include <Arduino.h>

void initializeOnboardLED() {
  pinMode(ledPin, OUTPUT);    // Initialize onboard LED
}

void turnLEDOn() {
  digitalWrite(ledPin, HIGH);
}

void turnLEDOff() {
  digitalWrite(ledPin, LOW);
}

void blink(byte numTimes) {
  while (numTimes-- > 0) {
    turnLEDOn();
    delay(250);
    turnLEDOff();
    delay(250);
  }
}
