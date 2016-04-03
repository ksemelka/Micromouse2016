#include <TimerOne.h>
#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
// #include "Floodfill.h"
#include "State.h"
#include "Maze.h"
#include "PIDencoders.h"

volatile int encoderLeftTicksPerSample = 0;
volatile int encoderRightTicksPerSample = 0;
volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;
int targetRight;
int targetLeft;

void checkIfTooClose();
bool isTooClose();

PID PID(.05, 0, 0);
Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

void setup() {
  Timer1.initialize(SAMPLE_TIME);
  Timer1.start();
  initializeOnboardLED();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial1.begin(9600);
  Timer1.attachInterrupt(readSensors);
  Timer1.attachInterrupt(calculateVelocity);
  attachInterrupt(encoderLEFT_A, countLeft, FALLING);
  attachInterrupt(encoderRIGHT_A, countRight, FALLING);
  Serial1.print("Starting...\n");
  while (sensors.getFrontSmoothed() < 500) {  // Wait to enter loop
//  sensors.view();
  }
  delay(2000);
  targetRight = analogRead(rightPT);
  targetLeft = analogRead(leftPT);
}

void loop() {
  sensors.view();
  navigate();
  delay(100);
  printState();
}

void countLeft() {
  encoderValueLeft++;
  encoderLeftTicksPerSample++;
}

void countRight() {
  encoderValueRight++;
  encoderRightTicksPerSample++;
}

void readSensors() {
      sensors.leftPTReading = analogRead(leftPT);
      sensors.frontPTReading = analogRead(frontPT);
      sensors.rightPTReading = analogRead(rightPT);
}
