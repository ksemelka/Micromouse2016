#include "Motors.h"
#include <Arduino.h>

extern int encoderValue;
extern int RIGHT_PinALast;

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
 void Motors::brake() {
   digitalWrite(LEFTMotorEN, HIGH);
   digitalWrite(LEFTlogic1, HIGH);
   digitalWrite(LEFTlogic2, HIGH);

   digitalWrite(RIGHTMotorEN, HIGH);
   digitalWrite(RIGHTlogic1, HIGH);
   digitalWrite(RIGHTlogic2, HIGH);
 }

void Motors::goForward() {
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  digitalWrite(RIGHTMotorEN, HIGH);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}

void Motors::goBackward() {
  digitalWrite(LEFTMotorEN, HIGH);
  digitalWrite(LEFTlogic1, LOW);
  digitalWrite(LEFTlogic2, HIGH);

  digitalWrite(RIGHTMotorEN, HIGH);
  digitalWrite(RIGHTlogic1, HIGH);
  digitalWrite(RIGHTlogic2, LOW);
}

void Motors::turnLeft() {
  encoderValue = 0;
  rotateCCW();
  while(true) {
    if (RIGHT_PinALast < encoderValue) {
      RIGHT_PinALast++;
      if (!(RIGHT_PinALast % 10)) {
        Serial.println(RIGHT_PinALast);
      }
    }
    if (encoderValue > 230) {
      brake();
      RIGHT_PinALast = 0;
      break;
    }
  }
}

void Motors::turnRight() {
  encoderValue = 0;
  rotateCW();
  while(true) {
    if (RIGHT_PinALast < encoderValue) {
      RIGHT_PinALast++;
      if (!(RIGHT_PinALast % 10)) {
        Serial.println(RIGHT_PinALast);
      }
    }
    if (encoderValue > 230) {
      brake();
      RIGHT_PinALast = 0;
      break;
    }
  }
}

void Motors::rotateCW() {
  Serial.println("Rotating CW");
  analogWrite(LEFTMotorEN, 255);
  digitalWrite(LEFTlogic1, LOW);
  digitalWrite(LEFTlogic2, HIGH);

  analogWrite(RIGHTMotorEN, 255);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}

void Motors::rotateCCW() {
  Serial.println("Rotating CCW");
  analogWrite(LEFTMotorEN, 255);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  analogWrite(RIGHTMotorEN, 255);
  digitalWrite(RIGHTlogic1, HIGH);
  digitalWrite(RIGHTlogic2, LOW);
}

void readEncoders() {

}
