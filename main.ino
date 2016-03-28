#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
#include "Floodfill.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int encoderValue = 0;
Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);
void count(void); // code for counting the increasing values of encoder ticks

void setup() {
  Serial.begin(9600);
  Serial.print("Starting...\n");
  attachInterrupt(encoderRIGHT_A, count, FALLING);
  delay(1000);
}

void loop() {
  motors.goForward();

  sensors.view();
  Serial.println();

//  sensors.mapPTReadings();
//  sensors.printMappedValues();
  Serial.println();

//  outputMappedValuesToLEDs();
   delay(1000);
   motors.halt();
   delay(1000);
   motors.goBackward();
 }

void count() {
  encoderValue++;
}
