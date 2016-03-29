#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

#define FRONT 1
#define RIGHT 2
#define LEFT 4

extern Sensors sensors;
// Values for how far the mouse should be from walls
int targetFront;
const int thresholdFront = 280;
int targetSide;
const int thresholdSide = 150;

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

void determineState() {
  switch (state()) {
    case 0:
      Serial.println("Error: 0");
      break;
    case 1:
      Serial.println("Error: 1 (FRONT)");
      break;
    case 2:
      Serial.println("Error: 2 (RIGHT)");
      break;
    case 4:
      Serial.println("Error: 4 (LEFT)");
      break;
    case 3:
      Serial.println("FRONT + RIGHT");
      break;
    case 5:
      Serial.println("FRONT + LEFT");
      break;
    case 6:
      Serial.println("RIGHT + LEFT");
      break;
    case 7:
      Serial.println("FRONT + LEFT + RIGHT");
      break;
    default:
      Serial.println("ERROR: Default");
  }
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
