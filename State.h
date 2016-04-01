#ifndef STATE_H
#define STATE_H
#include <Arduino.h>
#include "LEDs.h"

#define FRONT 1
#define RIGHT 2
#define LEFT 4

extern Sensors sensors;
extern Motors motors;
extern int calculateError();

// Values for how far the mouse should be from walls
//const int targetFront;
const int thresholdFront = 300;
//const int targetSide;
const int thresholdSide = 400;

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
      Serial1.println("Error: 0");
      break;
    case FRONT:
      Serial1.println("FRONT");
      break;
    case RIGHT:
      Serial1.println("RIGHT");
      break;
    case LEFT:
      Serial1.println("LEFT");
      break;
    case FRONT + RIGHT:
      Serial1.println("FRONT + RIGHT");
      break;
    case FRONT + LEFT:
      Serial1.println("FRONT + LEFT");
      break;
    case RIGHT + LEFT:
      Serial1.println("RIGHT + LEFT");
      break;
    case FRONT + LEFT + RIGHT:
      Serial1.println("FRONT + LEFT + RIGHT");
      break;
    default:
      Serial1.println("ERROR: Default");
  }
}

void navigate() {
  switch (state()) {
    case 0:
      Serial1.println("Error: 0");
      motors.halt();
      //blink(3);
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
      motors.goForwardProportional(calculateError());
      break;
    case LEFT:
      motors.goForwardProportional(calculateError());
      break;
    case FRONT + RIGHT:
      motors.turnLeft();
      break;
    case FRONT + LEFT:
      motors.turnRight();
      break;
    case RIGHT + LEFT:
      motors.goForwardProportional(calculateError());
      break;
    case FRONT + RIGHT + LEFT:
      motors.turnAround();
      break;
    default:
      motors.goForwardProportional(calculateError());
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
