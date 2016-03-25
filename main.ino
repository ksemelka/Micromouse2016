// PT == PHOTOTRANSISTOR
#include "Motors.h"
#include "PTs.h"
#include "LEDs.h"
#include "PID.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void setup() {
  Serial.begin(9600);
  delay(1000);
  initializeMotors();
  initializePTs();
//  initializeLEDs();
}
//volatile int encoderValue=0;
//
//void count(void); // code for counting the increasing values of encoder ticks
//void setup() {
//  Serial.begin(9600);
//  Serial.print("Start");
//  pinMode(encoderRIGHT_A, INPUT);
//  attachInterrupt(encoderRIGHT_A, count, FALLING);
//  encoderValue=0;
//}

//void loop() {
//  Serial.print("Starting\n");
//  delay(3000);
//  Serial.print("Encoder Value=");
//  Serial.println(encoderValue);
//  while (true) {
//    if (encoderValue > 500) {
//      break;
//    }
//  }
//}

void loop() {
  goForward();

  getPTReadings();
  printPTReadings();
  Serial.println();

  mapPTReadings();
  printMappedValues();
  Serial.println();

//  outputMappedValuesToLEDs();
   delay(2000);
   halt();
   delay(2000);
   goBackward();
 }

//void count() {
//  encoderValue++;
//}
