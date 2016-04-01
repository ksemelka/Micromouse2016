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
//const int targetFront;
const int thresholdFront = 280;
//const int targetSide;
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
    case FRONT:
      Serial.println("FRONT");
      break;
    case RIGHT:
      Serial.println("RIGHT");
      break;
    case LEFT:
      Serial.println("LEFT");
      break;
    case FRONT + RIGHT:
      Serial.println("FRONT + RIGHT");
      break;
    case FRONT + LEFT:
      Serial.println("FRONT + LEFT");
      break;
    case RIGHT + LEFT:
      Serial.println("RIGHT + LEFT");
      break;
    case FRONT + LEFT + RIGHT:
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
      motors.halt();
      blink(3);
      break;
    case FRONT:
      if (random(millis()) % 2) {   // Turn left or right randomly
        motors.turnLeft();
      }
      else {
        motors.turnRight();
      }
      break;
    case RIGHT:
      motors.turnLeft();
      break;
    case LEFT:
      motors.turnRight();
      break;
    case FRONT + RIGHT:
      motors.turnLeft();
      break;
    case FRONT + LEFT:
      motors.turnRight();
      break;
    case RIGHT + LEFT:
      motors.goForward();
      break;
    case FRONT + RIGHT + LEFT:
      motors.turnAround();
      break;
    default:
      motors.goForward();
  }
}

/*
  *********************************************************
  0 == undefined
  1 == FRONT                (Randomly choose left or right)
  2 == RIGHT                (Forward until wall)
  3 == FRONT + RIGHT        (Turn left)
  4 == LEFT                 (Forward until wall)
  5 == LEFT + FRONT         (Turn right)
  6 == LEFT + RIGHT         (Go forward)
  7 == LEFT + RIGHT + FRONT (Dead end, turn around)
  *********************************************************
*/

#endif /*STATE_H*/
