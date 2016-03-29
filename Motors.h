#ifndef MOTORS_H
#define MOTORS_H
#include <Arduino.h>

class Motors {
  public:
    Motors();
    void halt();
    // void coast();
    void brake();
    void goForward();
    void goBackward();
    void turnLeft();
    void turnRight();
    void rotateCCW();
    void rotateCW();
    void readEncoders();

  private:
<<<<<<< HEAD
    const byte LEFTMotorEN = 6;
    const byte LEFTlogic1 = 22;
    const byte LEFTlogic2 = 23;

    const byte RIGHTMotorEN = 7;
=======
    const byte LEFTMotorEN = 7;
    const byte LEFTlogic1 = 22;
    const byte LEFTlogic2 = 23;

    const byte RIGHTMotorEN = 6;
>>>>>>> refs/remotes/origin/master
    const byte RIGHTlogic1 = 9;
    const byte RIGHTlogic2 = 10;

    const byte encoderLEFT_A = 2;  // Left encoder output channel
    const byte encoderLEFT_B = 3;  // Left encoder output B
<<<<<<< HEAD

    const byte encoderRIGHT_A = 4; // Right encoder output channel
    const byte encoderRIGHT_B = 5; // Right encoder Output B
=======
    // int LEFTPos = 0;
    // int LEFT_PinALast = LOW;
    // int left = LOW;

    const byte encoderRIGHT_A = 4; // Right encoder output channel
    const byte encoderRIGHT_B = 5; // Right encoder Output B
    // int RIGHTPos = 0;
    // int RIGHT_PinALast = LOW;
    // int right = LOW;
>>>>>>> refs/remotes/origin/master
};

#endif  /*MOTORS_H*/
