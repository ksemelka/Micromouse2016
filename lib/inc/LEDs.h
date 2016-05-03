#ifndef LEDS_H
#define LEDS_H
#include <Arduino.h>

const byte ledPin = 13;

void initializeOnboardLED();
void turnLEDOn();
void turnLEDOff();
void blink(byte);

//const byte leftLED;  // FIXME: Connect LEDs to Arduino pins
//const byte middleLED;
//const byte rightLED;

//void initializeLEDs() {
//  pinMode(leftLED, OUTPUT);       // Initialize LEDs
//  pinMode(middleLED, OUTPUT);
//  pinMode(rightLED, OUTPUT);
//}

//void outputMappedValuesToLEDs() {
//  analogWrite(leftLED, leftMappedValue);
//  analogWrite(middleLED, middleMappedValue);
//  analogWrite(rightLED, rightMappedValue);
//}

#endif /*LEDS_H*/
