#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
//#include "Floodfill.h"
#include "State.h"
#include "Maze.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int RIGHT_PinALast = 0;
volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;
//extern const byte encoderLEFT_A;
//extern const byte encoderRIGHT_A;

void checkIfTooClose();
bool isTooClose();

Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

void setup() {
  initializeOnboardLED();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial1.begin(9600);
  attachInterrupt(motors.encoderLEFT_A, countLeft, FALLING);
  attachInterrupt(motors.encoderRIGHT_A, countRight, FALLING);
  Serial1.print("Starting...\n");
  delay(1000);
}

void loop() {
  
  sensors.readSensors();
  checkIfTooClose();
  if (!(millis() % 100)) {  // Prevent Serial buffer from being overloaded
    sensors.view();
    determineState();
  }
//  motors.turnRight();
//  
//  delay(1500);
//  checkIfTooClose();
  motors.goForward();
  delay(1000);
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

