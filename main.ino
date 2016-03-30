#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
#include "Floodfill.h"
#include "State.h"
#include "Maze.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int RIGHT_PinALast = 0;
volatile int encoderValue = 0;
const byte ledPin = 13;
extern const byte encoderLEFT_A;
extern const byte encoderRIGHT_A;

Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);
void count(void); // code for counting the increasing values of encoder ticks

void setup() {
  pinMode(ledPin, OUTPUT);    // Initialize onboard LED
  Serial.begin(9600);
  attachInterrupt(encoderLEFT_A, count, FALLING);
  attachInterrupt(encoderLEFT_A, count, FALLING);
  Serial.print("Starting...\n");
  delay(1000);
}

void loop() {
//  motors.turnRight();
//  delay(1000);
//  motors.turnLeft();
  if (!(millis() % 100)) {  // Prevent Serial buffer from being overloaded
    sensors.view();
    determineState();
  }
}

void count() {
  encoderValue++;
}

void printEncoderValues() {
  Serial.print("Encoder Value: ");
  Serial.println(encoderValue);
}
