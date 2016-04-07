#include <TimerOne.h>
#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
// #include "Floodfill.h"
#include "State.h"
#include "Maze.h"
#include "Encoder.h"
#include "pwm.h"

int encoderLeftTicksPerSample = 0;
int encoderRightTicksPerSample = 0;
volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;

int targetRight;
int targetLeft;

PID PID(.33, 0, 0);
Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

IntervalTimer sensorTimer;
IntervalTimer speedProfileTimer;

void setup() {
  sensorTimer.begin(readSensors, 1000);
  speedProfileTimer.begin(speedProfile, 1000);
  attachInterrupt(encoderLEFT_A, countLeftEncoder, RISING);
  attachInterrupt(encoderRIGHT_A, countRightEncoder, RISING);

  initializeOnboardLED();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial1.begin(9600);

  Serial1.print("Starting...\n");
  while (sensors.frontPTReading < 500) {  // Wait to enter loop
    blink(1);
  }
  delay(2000);
  targetRight = analogRead(rightPT);
  targetLeft = analogRead(leftPT);
}

void loop() {
  navigate();
}

void countLeftEncoder() {   // ++ if going forwards
 if (digitalRead(encoderLEFT_B) == HIGH) { // If channel A leads B, CW
   encoderValueLeft--;
 }
 else {
    encoderValueLeft++;
 }
}

void countRightEncoder() {  // ++ if going forwards
 if (digitalRead(encoderRIGHT_B) == HIGH) { // If channel A leads B, CW
    encoderValueRight++;
 }
 else {
    encoderValueRight--;
 }
}

void readSensors() {
  sensors.leftPTReading = analogRead(leftPT);
  sensors.frontPTReading = analogRead(frontPT);
  sensors.rightPTReading = analogRead(rightPT);
}

void speedProfile() {
  getEncoderStatus();
  updateCurrentSpeed();
  calculateMotorPwm();
}

void calculateVelocity() {
  PID.velocityLeft = (double)encoderLeftTicksPerSample / VELOCITY_SAMPLE_TIME;
  PID.velocityRight = (double)encoderRightTicksPerSample / VELOCITY_SAMPLE_TIME;
  PID.calculateProportionalEncoderError();
  PID.prevVelocityLeft = PID.velocityLeft;  // Keep these values for calculating error
  PID.prevVelocityRight = PID.velocityRight;
  encoderLeftTicksPerSample = 0;
  encoderRightTicksPerSample = 0;
}
