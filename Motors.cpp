#include "Motors.h"
#include <Arduino.h>

Motors::Motors() {
  pinMode(LEFTMotorEN, OUTPUT);  // Initialize left motor
  pinMode(LEFTlogic1, OUTPUT);
  pinMode(LEFTlogic2, OUTPUT);

  digitalWrite(LEFTMotorEN, LOW);

  pinMode(RIGHTMotorEN, OUTPUT);  // Initialize right motor
  pinMode(RIGHTlogic1, OUTPUT);
  pinMode(RIGHTlogic2, OUTPUT);

  digitalWrite(RIGHTMotorEN, LOW);

  pinMode(encoderLEFT_A, INPUT);  // Initialize left encoder
  pinMode(encoderLEFT_B, INPUT);

  pinMode(encoderRIGHT_A, INPUT); // Initialize right encoder
  pinMode(encoderRIGHT_B, INPUT);
}

void Motors::halt() {
  digitalWrite(LEFTMotorEN, LOW);
  digitalWrite(RIGHTMotorEN, LOW);
}

// void Motors::coast() {
//   digitalWrite(LEFTMotorEN, HIGH);
//   digitalWrite(LEFTlogic1, LOW);
//   digitalWrite(LEFTlogic2, LOW);
//
//   digitalWrite(RIGHTMotorEN, HIGH);
//   digitalWrite(RIGHTlogic1, LOW);
//   digitalWrite(RIGHTlogic2, LOW);
// }
//
// void Motors::break() {
//   digitalWrite(LEFTMotorEN, HIGH);
//   digitalWrite(LEFTlogic1, HIGH);
//   digitalWrite(LEFTlogic2, HIGH);
//
//   digitalWrite(RIGHTMotorEN, HIGH);
//   digitalWrite(RIGHTlogic1, HIGH);
//   digitalWrite(RIGHTlogic2, HIGH);
// }

void Motors::goForward() {
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  digitalWrite(RIGHTMotorEN, HIGH);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}

void Motors::goBackward() {                       // FIXME:20 This doesn't work, makes it go forwards instead
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(LEFTlogic1, LOW);
  digitalWrite(LEFTlogic2, HIGH);

  digitalWrite(RIGHTMotorEN, HIGH);
  digitalWrite(RIGHTlogic1, HIGH);
  digitalWrite(RIGHTlogic2, LOW);
}

void Motors::turnLeft() {
  rotateCCW();
  while(true) {
    if (encoderValue > 94) {
      encoderValue = 0;
      break;
    }
  }
}

void Motors::turnRight() {
  rotateCW();
  while(true) {
    if (encoderValue > 94) {
      encoderValue = 0;
      break;
    }
  }
}

void Motors::rotateCCW() {
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(LEFTlogic1, LOW);
  digitalWrite(LEFTlogic2, HIGH);

  digitalWrite(RIGHTMotorEN, HIGH);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}

void Motors::rotateCW() {
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  digitalWrite(RIGHTMotorEN, HIGH);
  digitalWrite(RIGHTlogic1, HIGH);
  digitalWrite(RIGHTlogic2, LOW);
}
