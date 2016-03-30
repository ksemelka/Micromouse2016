#ifndef STATE_H
#define STATE_H
#include <Arduino.h>
#include "LEDs.h"

#define FRONT 1
#define RIGHT 2
#define LEFT 4

extern Sensors sensors;
extern Motors motors;
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
      Serial.println("FRONT");
      break;
    case 2:
      Serial.println("RIGHT");
      break;
    case 4:
      Serial.println("LEFT");
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

void navigate() {
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

    // FRONT + RIGHT
    case 3:
      motors.turnLeft();
      break;

    // FRONT + LEFT
    case 5:
      motors.turnRight();
      break;
    case 6:
      Serial.println("RIGHT + LEFT");
      break;
    case 7:
      Serial.println("FRONT + LEFT + RIGHT");
      break;
    default:
      motors.goForward();
  }
}

/*
  *******************************************************
  0 == undefined
  1 == FRONT                (Shouldn't happen, undefined)
  2 == RIGHT                (Forward until wall)
  3 == FRONT + RIGHT        (Turn left)
  4 == LEFT                 (Forward until wall)
  5 == LEFT + FRONT         (Turn right)
  6 == LEFT + RIGHT         (Go forward)
  7 == LEFT + RIGHT + FRONT (Dead end, turn around)
  *******************************************************
*/

#endif /*STATE_H*/
