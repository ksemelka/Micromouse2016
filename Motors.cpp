#include "Motors.h"
#include <Arduino.h>

extern int calculateError();
extern int encoderValueLeft;
extern int encoderValueRight;

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

void Motors::goForwardProportional(int error) {
  analogWrite(LEFTMotorEN, 80 - (error/2));         //tuned down from 128
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  analogWrite(RIGHTMotorEN, 80 + (error/2));      //tuned down
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
  encoderValueLeft = 0;
  encoderValueRight = 0;
  rotateCCW();
  while(true) {
    if (LEFT_PinALast < encoderValueLeft) {
      LEFT_PinALast++;
    }
    if (RIGHT_PinALast < encoderValueRight) {
      RIGHT_PinALast++;
    }
    if (!((LEFT_PinALast + RIGHT_PinALast) % 10)) {
      Serial1.println(LEFT_PinALast + RIGHT_PinALast);
    }
    if (encoderValueRight + encoderValueLeft > 365) {
        brake();
        LEFT_PinALast = 0;
        RIGHT_PinALast = 0;
        break;
    }
  }
}

void Motors::turnRight() {
  encoderValueLeft = 0;
  encoderValueRight = 0;
  rotateCW();
  while(true) {
    if (LEFT_PinALast < encoderValueLeft) {
      LEFT_PinALast++;
    }
    if (RIGHT_PinALast < encoderValueRight) {
      RIGHT_PinALast++;
    }
    if (!((LEFT_PinALast + RIGHT_PinALast) % 10)) {
      Serial1.println(LEFT_PinALast + RIGHT_PinALast);
    }
    if (encoderValueLeft + encoderValueRight > 335) {
         brake();
         LEFT_PinALast = 0;
         RIGHT_PinALast = 0;
         break;
    }
  }
}

void Motors::turnAround() {
  encoderValueLeft = 0;
  encoderValueRight = 0;
  rotateCW();
  while(true) {
    if (LEFT_PinALast < encoderValueLeft) {
      LEFT_PinALast++;
    }
    if (RIGHT_PinALast < encoderValueRight) {
      RIGHT_PinALast++;
    }
    if (!((RIGHT_PinALast + LEFT_PinALast) % 10)) {
      Serial1.println(RIGHT_PinALast + LEFT_PinALast);
    }
    if (encoderValueLeft + encoderValueRight > 910) {
      brake();
      LEFT_PinALast = 0;
      RIGHT_PinALast = 0;
      break;
    }
  }
}

void Motors::rotateCW() {
  Serial1.println("Rotating CW");
  analogWrite(LEFTMotorEN, 150);
  digitalWrite(LEFTlogic1, LOW);
  digitalWrite(LEFTlogic2, HIGH);

  analogWrite(RIGHTMotorEN, 150);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}

void Motors::rotateCCW() {
  Serial1.println("Rotating CCW");
  analogWrite(LEFTMotorEN, 150);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  analogWrite(RIGHTMotorEN, 150);
  digitalWrite(RIGHTlogic1, HIGH);
  digitalWrite(RIGHTlogic2, LOW);
}

void Motors::traverseCell() {
  encoderValueLeft = 0;
  encoderValueRight = 0;
  while (encoderValueLeft + encoderValueRight < encoderTicksPerCell) {
    // goForwardProportional(calculateError());
    goForward();
  }
}
