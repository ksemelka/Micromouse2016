#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
// #include "Floodfill.h"
#include "State.h"
#include "Maze.h"
#include "Encoder.h"
#include "pwm.h"
#include "Buzzer.h"

volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;

Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

IntervalTimer sensorTimer;
IntervalTimer speedProfileTimer;
elapsedMillis wait;

void setup() {
  attachInterrupts();
  initializeTimers();
  initializeOnboardLED();
  initializeBuzzer();
  bootTone();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial.begin(9600);
  Serial1.print("Starting...\n");
  turnMotorENOff;
  while (sensors.frontPTReading < 500) {  // Wait to enter loop
    blink(1);
  }
//  chirp();
  delay(2000);
  turnMotorENOn;
  calibrateTargetValues();
  wait = 0;
}
void loop() {
//  turnMotorENOff;
//  if (wait > 500) {
//    outputData(targetFront, thresholdFront);
//    outputData(targetLeft, targetRight);
//    outputData(thresholdSide);
//    Serial.print("\n");
//    wait -= 500;
//  }
  newSolveRightHand();
  delay(200);
}

void outputData(double data) {
  Serial.println(data);
}
void outputData(double left, double right) {
  Serial.print(left);
  Serial.print("/");
  Serial.println(right);
}

void countLeftEncoderA() {   // ++ if going forwards
  if (digitalRead(encoderLEFT_A)) {
    if (digitalRead(encoderLEFT_B)) { // If channel A leads B, CW
      encoderValueLeft--;
    }
    else {
      encoderValueLeft++;
    }
  }
  else {
    if (digitalRead(encoderLEFT_B)) {
      encoderValueLeft++;
    }
    else {
      encoderValueLeft--;
    }
  }
}

void countRightEncoderA() {  // ++ if going forwards
  if (digitalRead(encoderRIGHT_A)) {
    if (digitalRead(encoderRIGHT_B)) { // If channel A leads B, CW
      encoderValueRight--;
    }
    else {
      encoderValueRight++;
    }
  }
  else {
    if (digitalRead(encoderRIGHT_B)) { // If channel A leads B, CW
      encoderValueRight++;
    }
    else {
      encoderValueRight--;
    }
  }
}

void countLeftEncoderB() {
  if (digitalRead(encoderLEFT_B)) {
    if (digitalRead(encoderLEFT_A)) {
      encoderValueLeft++;
    }
    else {
      encoderValueLeft--;
    }
  }
  else {
    if (digitalRead(encoderLEFT_A)) {
      encoderValueLeft--;
    }
    else {
      encoderValueLeft++;
    }
  }
}

void countRightEncoderB() {
  if (digitalRead(encoderRIGHT_B)) {
    if (digitalRead(encoderRIGHT_A)) {
      encoderValueRight++;
    }
    else {
      encoderValueRight--;
    }
  }
  else {
    if (digitalRead(encoderRIGHT_A)) {
      encoderValueRight--;
    }
    else {
      encoderValueRight++;
    }
  }
}

void speedProfile() {
  getEncoderStatus();
  updateCurrentSpeed();
  calculateMotorPwm();
}

void readSensors() {
  sensors.leftPTReading = analogRead(leftPT);
  sensors.frontPTReading = analogRead(frontPT);
  sensors.rightPTReading = analogRead(rightPT);
  calculateSensorError();
}

void calibrateTargetValues() {
  resetSpeedProfile();
  targetRight = sensors.rightPTReading;
  targetLeft = sensors.leftPTReading;
  thresholdSide = (targetRight + targetLeft) / 7.5;
  turnRightEncoderTicks();
  targetFront = sensors.frontPTReading;
  thresholdFront = targetFront / 10;
  turnLeftEncoderTicks();
}

void initializeTimers() {
  sensorTimer.begin(readSensors, 5000);
  sensorTimer.priority(172);
  speedProfileTimer.begin(speedProfile, 5000);
  speedProfileTimer.priority(172);
}

void attachInterrupts() {
  attachInterrupt(encoderLEFT_A, countLeftEncoderA, CHANGE);
  attachInterrupt(encoderRIGHT_A, countRightEncoderA, CHANGE);
  attachInterrupt(encoderLEFT_B, countLeftEncoderB, CHANGE);
  attachInterrupt(encoderRIGHT_B, countRightEncoderB, CHANGE);
}
