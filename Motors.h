#ifndef MOTORS_H
#define MOTORS_H
#include <Arduino.h>

#define encoderLEFT_A       2  // Left encoder output channel
#define encoderLEFT_B       3  // Left encoder output B
#define encoderRIGHT_A      4  // Right encoder output channel
#define encoderRIGHT_B      5  // Right encoder Output B
#define encoderTicksPerCell 1475  // Number of encoder ticks it takes to traverse cell

class Motors {
  public:
    Motors();
    void halt();
    // void coast();
    void brake();
    void goForward();
    void goForwardProportional(int);
    void goBackward();
    void turnLeft();
    void turnRight();
    void turnAround();
    void rotateCCW();
    void rotateCW();
    void traverseCell();
    // void checkIfTooClose();
    // bool isTooClose();

  // private:
    const byte LEFTMotorEN = 6;
    const byte LEFTlogic1 = 22;
    const byte LEFTlogic2 = 23;

    const byte RIGHTMotorEN = 7;
    const byte RIGHTlogic1 = 9;
    const byte RIGHTlogic2 = 10;
};

#endif  /*MOTORS_H*/
