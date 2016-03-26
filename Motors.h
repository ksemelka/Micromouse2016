#ifndef MOTORS_H
#define MOTORS_H

const byte LEFTMotorEN = 5;
const byte LEFTlogic1 = 6;
const byte LEFTlogic2 = 7;

const byte RIGHTMotorEN = 2;
const byte RIGHTlogic1 = 3;
const byte RIGHTlogic2 = 4;

const byte encoderLEFT_A = A4;  // Left encoder output channel
const byte encoderLEFT_B = A3;  // Left encoder output B
// int LEFTPos = 0;
// int LEFT_PinALast = LOW;
// int left = LOW;

const byte encoderRIGHT_A = A6; // Right encoder output channel
const byte encoderRIGHT_B = A5; // Right encoder Output B
// int RIGHTPos = 0;
// int RIGHT_PinALast = LOW;
// int right = LOW;

class Motors {
  public:
    Motors() {
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
    void halt() {
      digitalWrite(LEFTMotorEN, LOW);
      digitalWrite(RIGHTMotorEN, LOW);
    }
    // void coast() {
    //   digitalWrite(LEFTMotorEN, HIGH);
    //   digitalWrite(LEFTlogic1, LOW);
    //   digitalWrite(LEFTlogic2, LOW);
    //
    //   digitalWrite(RIGHTMotorEN, HIGH);
    //   digitalWrite(RIGHTlogic1, LOW);
    //   digitalWrite(RIGHTlogic2, LOW);
    // }
    // void brake() {
    //   digitalWrite(LEFTMotorEN, HIGH);
    //   digitalWrite(LEFTlogic1, HIGH);
    //   digitalWrite(LEFTlogic2, HIGH);
    //
    //   digitalWrite(RIGHTMotorEN, HIGH);
    //   digitalWrite(RIGHTlogic1, HIGH);
    //   digitalWrite(RIGHTlogic2, HIGH);
    // }
    void goForward() {
      digitalWrite(LEFTMotorEN, HIGH);
      digitalWrite(LEFTlogic1, HIGH);
      digitalWrite(LEFTlogic2, LOW);

      digitalWrite(RIGHTMotorEN, HIGH);
      digitalWrite(RIGHTlogic1, LOW);
      digitalWrite(RIGHTlogic2, HIGH);
    }
    void goBackward() {                       // FIXME:20 This doesn't work, makes it go forwards instead
      digitalWrite(LEFTMotorEN, HIGH);
      digitalWrite(LEFTlogic1, LOW);
      digitalWrite(LEFTlogic2, HIGH);

      digitalWrite(RIGHTMotorEN, HIGH);
      digitalWrite(RIGHTlogic1, HIGH);
      digitalWrite(RIGHTlogic2, LOW);
    }

    // TODO: Implement turnLeft() and turnRight() functions

    void turnLeft() {                     // IDEA: Figure out how many ticks of an encoder it takes to turn 90 degrees
      digitalWrite(LEFTMotorEN, LOW);
      digitalWrite(RIGHTMotorEN, HIGH);
    }
};


#endif  /*MOTORS_H*/
