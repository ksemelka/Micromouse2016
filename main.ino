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
volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;
extern const byte encoderLEFT_A;
extern const byte encoderRIGHT_A;

Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);
void count(); // code for counting the increasing values of encoder ticks

void setup() {
  initializeOnboardLED();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial.begin(9600);
  attachInterrupt(motors.encoderLEFT_A, countLeft, FALLING);
  attachInterrupt(motors.encoderRIGHT_A, countRight, FALLING);
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

void countLeft() {
  encoderValueLeft++;
}

void countRight() {
  encoderValueRight++;
}

void printEncoderValues() {
  Serial.print("Encoder Value: ");
  Serial.println(encoderValueLeft);
}
