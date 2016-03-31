#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
// #include "Floodfill.h"
#include "State.h"
#include "Maze.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define OFFSET 0
int error = 0;

void calculateError() {
  sensors.readSensors();
  error = sensors.getRightPTReading() - sensors.getLeftPTReading() - OFFSET;
}

volatile int RIGHT_PinALast = 0;
volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;

Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

void setup() {
  initializeOnboardLED();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial.begin(9600);
  attachInterrupt(encoderLEFT_A, countLeft, FALLING);
  attachInterrupt(encoderRIGHT_A, countRight, FALLING);
  Serial.print("Starting...\n");
  delay(1000);
}

void loop() {
  motors.goForwardProportional(calculateError());
  if (sensors.getFrontPTReading() > 950) {  // Prevent motor driver from burning out
    motors.brake();
  }
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
