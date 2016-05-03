#ifndef MOTORS_H
#define MOTORS_H
#include <Arduino.h>

#define turnMotorENOff      digitalWrite(LEFTMotorEN, LOW);digitalWrite(RIGHTMotorEN, LOW)
#define turnMotorENOn       digitalWrite(LEFTMotorEN, HIGH); digitalWrite(RIGHTMotorEN, HIGH)

#define encoderLEFT_A       2  // Left encoder output channel
#define encoderLEFT_B       3  // Left encoder output B
#define encoderRIGHT_A      5  // Right encoder output channel
#define encoderRIGHT_B      4  // Right encoder Output B
#define encoderTicksPerCell 1475  // Number of encoder ticks it takes to traverse cell

#define RIGHTMotorEN    6
#define RIGHTlogic1     22
#define RIGHTlogic2     23

#define LEFTMotorEN     7
#define LEFTlogic1      9
#define LEFTlogic2      10

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
};

#endif  /*MOTORS_H*/
