#include "lib/inc/Motors.h"
#include "lib/inc/Sensors.h"
#include "lib/inc/LEDs.h"
#include "lib/inc/Floodfill.h"
#include "lib/inc/State.h"
#include "lib/inc/Maze.h"
#include "lib/inc/Encoder.h"
#include "lib/inc/pwm.h"
#include "lib/inc/Buzzer.h"
#include "lib/inc/Cell.h"
#include "lib/inc/CellStack.h"


volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;
double adj = 1.0;
bool rightHand = false;
byte nextState = LEFT + RIGHT;
Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);

IntervalTimer sensorTimer;
IntervalTimer speedProfileTimer;
elapsedMillis wait;

void setup() {
  mazeSetup();
  floodStack.push(liveMaze[xPos][yPos]); //Push Current cell
  attachInterrupts();
  initializeTimers();
  initializeOnboardLED();
  initializeBuzzer();
  bootTone();
  randomSeed(analogRead(0));  // Seeds using random analog noise on unconnected pin
  Serial1.begin(9600);
  Serial1.print("Starting...\n");
  turnMotorENOff;
  
  while (sensors.frontPTReading < 500) {  // Wait to enter loop
    turnLEDOn();
  }
  turnLEDOff();
  if (sensors.rightPTReading > 550) {
      rightHand = true;
      playTone(150, 50);
      delay(150);
      playTone(200, 50);
      delay(150);
      playTone(150, 50);
      delay(500);
  }

  if (sensors.leftPTReading > 550) {
      playTone(1000, 50);
      delay(200);
      playTone(2000, 50);
      delay(200);
      playTone(1000, 50);
      delay(200);
      delay(2000);
  
    while(sensors.frontPTReading < 500){
      //outputData(encoderValueLeft);
      //delay(100);

      if((encoderValueLeft > -250) && (encoderValueLeft <250)){
//        Serial.println("C2");
        playTone(527, 100);
        adj = 1.0;
      }
      
      if((encoderValueLeft >= 250) && (encoderValueLeft <500)){
//        Serial.println("D");
        playTone(470, 100);
        adj = 1.1;
      }
      
      if((encoderValueLeft >= 500) && (encoderValueLeft <750)){
//        Serial.println("E");
        playTone(419, 100);
        adj = 1.1;
      }

      if((encoderValueLeft >= 750) && (encoderValueLeft <1000)){
//        Serial.println("F");
        playTone(395, 100);
        adj = 1.2;
      }

      if((encoderValueLeft >= 1000) && (encoderValueLeft <1250)){
//        Serial.println("G");
        playTone(352, 100);
        adj = 1.3;
      }

      if((encoderValueLeft >= 1250) && (encoderValueLeft <1500)){
//        Serial.println("A");
        playTone(314, 100);
        adj = 1.4;
      }

      if((encoderValueLeft >= 1500) && (encoderValueLeft <1750)){
//        Serial.println("B");
        playTone(279, 100);
        adj = 1.5;
      }

      if(encoderValueLeft >= 1750){
//        Serial.println("CHigh");
        playTone(264, 100);
        adj = 1.6;
      }


 if((encoderValueLeft > -500) && (encoderValueLeft <=-250)){
//        Serial.println("Bminus");
        playTone(559, 100);
        adj = 0.9;
      }

      if((encoderValueLeft > -750) && (encoderValueLeft <=-500)){
//        Serial.println("Aminus");
        playTone(627, 100);
        adj = 0.8;
      }

      if((encoderValueLeft > -1000) && (encoderValueLeft <=-750)){
//        Serial.println("Gminus");
        playTone(704, 100);
        adj = 0.7;
      }

      if((encoderValueLeft > -1250) && (encoderValueLeft <=-1000)){
//        Serial.println("Fminus");
        playTone(790, 100);
        adj = 0.6;
      }

      if((encoderValueLeft > -1500) && (encoderValueLeft <=-1250)){
//        Serial.println("Eminus");
        playTone(837, 100);
        adj = 0.5;
      }

      if((encoderValueLeft > -1750) && (encoderValueLeft <=-1500)){
//        Serial.println("D");
        playTone(940, 100);
        adj = 0.4;
      }

      if(encoderValueLeft <= -1750){
//        Serial.println("CLow");
        playTone(1055, 100);
        adj = 0.3;
      }

    }

  }

  chirp();
  delay(1000);
  turnMotorENOn;
  calibrateTargetValues();
  wait = 0;
  startTone();
}




void loop() {
  if (rightHand) {
    newSolveRightHand();
  }
  else {
    step();
    floodfill();
    analyzePosition();
  }
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
  targetRight = sensors.rightPTReading * adj;
  targetLeft = sensors.leftPTReading * adj;
  thresholdSide = (targetRight + targetLeft) / 5.5; // 7.5
  turnRightEncoderTicks();
  targetFront = sensors.frontPTReading * adj;
  thresholdFront = targetFront / 12;  // 10
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
