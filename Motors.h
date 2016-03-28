#ifndef MOTORS_H
#define MOTORS_H
#include <Arduino.h>

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
    Motors();
    void halt();
    // void coast();
    // void break();
    void goForward();
    void goBackward();
    void turnLeft();
    void turnRight();
    void rotateCCW();
    void rotateCW();
};


#endif  /*MOTORS_H*/
