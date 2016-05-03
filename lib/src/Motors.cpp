#include "../inc/Motors.h"
#include "../inc/Sensors.h"
#include "../inc/LEDs.h"
#include "../inc/State.h"
#include "../inc/Encoder.h"
#include <Arduino.h>


extern Sensors sensors;
extern int encoderValueLeft;
extern int encoderValueRight;
extern byte nextState;

Motors::Motors() {
  pinMode(LEFTMotorEN, OUTPUT);  // Initialize left motor
  pinMode(LEFTlogic1, OUTPUT);
  pinMode(LEFTlogic2, OUTPUT);



  pinMode(RIGHTMotorEN, OUTPUT);  // Initialize right motor
  pinMode(RIGHTlogic1, OUTPUT);
  pinMode(RIGHTlogic2, OUTPUT);

  turnMotorENOn;

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
  analogWrite(LEFTMotorEN, 180);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  analogWrite(RIGHTMotorEN, 150);
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
    delay(2);
    if (encoderValueRight + encoderValueLeft > 380) {
      break;
    }
  }
  brake();
}

void Motors::turnRight() {
  encoderValueLeft = 0;
  encoderValueRight = 0;
  rotateCW();
  while(true) {
    delay(2);
    if (encoderValueLeft + encoderValueRight > 351) {
      break;
    }
  }
  brake();
}

void Motors::turnAround() {
  encoderValueLeft = 0;
  encoderValueRight = 0;
  rotateCW();
  while(true) {
    delay(1);
    if (encoderValueLeft + encoderValueRight > 904) {
      break;
    }
  }
  brake();
}

void Motors::rotateCW() {
  analogWrite(LEFTMotorEN, 130);
  digitalWrite(LEFTlogic1, LOW);
  digitalWrite(LEFTlogic2, HIGH);

  analogWrite(RIGHTMotorEN, 130);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}

void Motors::rotateCCW() {
  analogWrite(LEFTMotorEN, 130);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);

  analogWrite(RIGHTMotorEN, 130);
  digitalWrite(RIGHTlogic1, HIGH);
  digitalWrite(RIGHTlogic2, LOW);
}

void Motors::goForwardProportional(int error) {
  analogWrite(LEFTMotorEN, 180 - error);
  digitalWrite(LEFTlogic1, HIGH);
  digitalWrite(LEFTlogic2, LOW);
  analogWrite(RIGHTMotorEN, 150 + error);
  digitalWrite(RIGHTlogic1, LOW);
  digitalWrite(RIGHTlogic2, HIGH);
}

void Motors::traverseCell() {
  encoderValueLeft = 0;
  encoderValueRight = 0;
  while (encoderValueLeft + encoderValueRight < encoderTicksPerCell) {
    // goForwardProportional(PID.calculateError());
    if (encoderValueLeft + encoderValueRight > encoderTicksPerCell - 500 &&
        encoderValueLeft + encoderValueRight < encoderTicksPerCell - 495) { // Call within a range
                                                                            // in case they increment
                                                                            // by more than 1 at a time
        nextState = state();
    }
    if (sensors.frontPTReading > targetFront) {
      nextState = state();
      break;
    }
  }
  brake();
  // oldEncoderCount = encoderCount;
}

// void Motors::checkIfTooClose() {
//   if (isTooClose()) {
//     while (true) {
//       Serial1.println("Stopped: Too close");
//       blink(1);
//     }
//   }
//  }
//
// bool Motors::isTooClose() {
//   sensors.readSensors();
//   if (sensors.getFrontPTReading() > 964) {  // Prevent motor driver from burning out
//     brake();
//     return true;
//   }
//   return false;
// }
