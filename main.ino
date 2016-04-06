#include <TimerOne.h>
#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
// #include "Floodfill.h"
#include "State.h"
#include "Maze.h"
<<<<<<< HEAD
#include "PIDencoders.h"

volatile int encoderLeftTicksPerSample = 0;
volatile int encoderRightTicksPerSample = 0;
=======
// #include "stm32f4xx.h"
// #include "delay.h"

>>>>>>> refs/remotes/origin/master
volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;
int targetRight;
int targetLeft;

void checkIfTooClose();
bool isTooClose();

PID PID(.33, 0, 0);
Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

void setup() {
<<<<<<< HEAD
  Timer1.initialize(VELOCITY_SAMPLE_TIME);
=======
  Timer1.initialize(500);
>>>>>>> refs/remotes/origin/master
  Timer1.start();
  initializeOnboardLED();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial1.begin(9600);
<<<<<<< HEAD
  Serial.begin(9600);
  Timer1.attachInterrupt(calculateVelocity);
  attachInterrupt(encoderLEFT_A, countLeft, FALLING);
  attachInterrupt(encoderRIGHT_A, countRight, FALLING);
  Serial1.print("Starting...\n");
  delay(1000);
  while (sensors.getFrontSmoothed() < 500 || !(millis() % 300)) {  // Wait to enter loop
    sensors.view();
=======
  Timer1.attachInterrupt(readSensors);
  attachInterrupt(encoderLEFT_A, countLeft, RISING);
  attachInterrupt(encoderRIGHT_A, countRight, RISING);
  Serial1.print("Starting...\n");
  while (sensors.frontPTReading < 500) {  // Wait to enter loop
    blink(1);
>>>>>>> refs/remotes/origin/master
  }
  delay(2000);
  targetRight = analogRead(rightPT);
  targetLeft = analogRead(leftPT);
}

void loop() {
<<<<<<< HEAD
//  sensors.view();
  navigate();
  delay(1000);
//  printState();
//  if (!(millis() % 300)) {
    sensors.view();
//    Serial1.println(PID.velocityLeft);
//    Serial1.print("Velocity Right: ")
//    Serial1.println(PID.velocityRight);
//  }
//  motors.goForward();
//  motors.goForwardProportional(PID.calculateError());
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
=======
  navigate();
}

void countLeft() {
//  if (digitalRead(encoderLEFT_B) == HIGH) { // If channel A leads B, CW
//    encoderValueLeft--;
//  }
//  else {
    encoderValueLeft++;
//  }
}

void countRight() {
//  if (digitalRead(encoderRIGHT_B) == HIGH) { // If channel A leads B, CW
    encoderValueRight++;
//  }
//  else {
//    encoderValueRight--;
//  }
}

void readSensors() {
  sensors.leftPTReading = analogRead(leftPT);
  sensors.frontPTReading = analogRead(frontPT);
  sensors.rightPTReading = analogRead(rightPT);
>>>>>>> refs/remotes/origin/master
}

void calculateVelocity() {
  sensors.leftSmoothed = analogRead(leftPT);
  sensors.frontSmoothed = analogRead(frontPT);
  sensors.rightSmoothed = analogRead(rightPT);
  PID.velocityLeft = (double)encoderLeftTicksPerSample / VELOCITY_SAMPLE_TIME;
  PID.velocityRight = (double)encoderRightTicksPerSample / VELOCITY_SAMPLE_TIME;
  PID.calculateProportionalEncoderError();
  PID.prevVelocityLeft = PID.velocityLeft;  // Keep these values for calculating error
  PID.prevVelocityRight = PID.velocityRight;
  encoderLeftTicksPerSample = 0;
  encoderRightTicksPerSample = 0;
}
