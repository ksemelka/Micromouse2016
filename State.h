#ifndef STATE_H
#define STATE_H

#define FRONT 1
#define RIGHT 2
#define LEFT 4
extern Sensors sensors;

// Values for how far the mouse should be from walls
int targetFront;
const int thresholdFront = 300;
int targetSide;
const int thresholdSide = 350;

byte state() {
  byte currentState = 0;
  sensors.readSensors();

  if (sensors.getFrontPTReading() > thresholdFront) {
    currentState += FRONT;
  }
  if (sensors.getRightPTReading() > thresholdSide) {
    currentState += RIGHT;
  }
  if (sensors.getLeftPTReading() > thresholdSide) {
    currentState += LEFT;
  }
  return currentState;
}

/*
  ************
  0 == undefined
  1 == FRONT                (Shouldn't happen, undefined)
  2 == RIGHT                (Shouldn't happen, undefined)
  3 == FRONT + RIGHT        (Turn left)
  4 == LEFT                 (Shouldn't happen, undefined)
  5 == LEFT + FRONT         (Turn right)
  6 == LEFT + RIGHT         (Go forward)
  7 == LEFT + RIGHT + FRONT (Dead end)
*/

#endif /*STATE_H*/
