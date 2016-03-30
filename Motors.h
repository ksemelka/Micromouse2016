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
    void turnAround();
    void rotateCCW();
    void rotateCW();
    
    const byte encoderLEFT_A = 2;  // Left encoder output channel
    const byte encoderLEFT_B = 3;  // Left encoder output B

    const byte encoderRIGHT_A = 4; // Right encoder output channel
    const byte encoderRIGHT_B = 5; // Right encoder Output B

  private:
    const byte LEFTMotorEN = 6;
    const byte LEFTlogic1 = 22;
    const byte LEFTlogic2 = 23;

    const byte RIGHTMotorEN = 7;
    const byte RIGHTlogic1 = 9;
    const byte RIGHTlogic2 = 10;
};

#endif  /*MOTORS_H*/
