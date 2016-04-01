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

int calculateError() {
  int error = 0;
  sensors.readSensors();
  error = sensors.getRightPTReading() - sensors.getLeftPTReading() - OFFSET;
  return error;
}

volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;

void checkIfTooClose();
bool isTooClose();

Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

void setup() {
  initializeOnboardLED();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial1.begin(9600);
  attachInterrupt(encoderLEFT_A, countLeft, FALLING);
  attachInterrupt(encoderRIGHT_A, countRight, FALLING);
  Serial1.print("Starting...\n");
  delay(1000);
}

void loop() {
  checkIfTooClose();
  motors.goForwardProportional(calculateError());
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
  Serial1.print("Encoder Value: ");
  Serial1.println(encoderValueLeft);
}

void checkIfTooClose() {
  if (isTooClose()) {
    while (true) {
      Serial1.println("Stopped: Too close");
      blink(1);
    }
  }
 }

bool isTooClose() {
  sensors.readSensors();
  if (sensors.getFrontPTReading() > 964) {  // Prevent motor driver from burning out
    motors.brake();
    return true;
  }
  return false;
}
