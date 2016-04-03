#include "State.h"
#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include <Arduino.h>

extern Motors motors;
extern Sensors sensors;

bool wallToTheFront() {
  if (sensors.getFrontSmoothed() > thresholdFront) {
    return true;
  }
  return false;
}

bool wallToTheRight() {
  if (sensors.getRightSmoothed() > thresholdSide) {
    return true;
  }
  return false;
}

bool wallToTheLeft() {
  if (sensors.getLeftSmoothed() > thresholdSide) {
    return true;
  }
  return false;
}

byte state() {
  byte currentState = 0;
//  sensors.readSensors();
  if (wallToTheFront()) {
    currentState += FRONT;
  }
  if (wallToTheRight()) {
    currentState += RIGHT;
  }
  if (wallToTheLeft()) {
    currentState += LEFT;
  }
  return currentState;
}

void printState() {
  switch (state()) {
    case 0:
      Serial1.println("STATE: 0");
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
  printState();
  switch (state()) {
    case 0:
      motors.traverseCell();

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
      if (random(millis()) % 2) {   // Turn left or go forward randomly
        motors.turnLeft();
      }
      else {
        motors.traverseCell();
      }
      break;
    case LEFT:
      if (random(millis()) % 2) {   // Turn right or go forward randomly
        motors.turnRight();
      }
      else {
        motors.traverseCell();
      }
      break;
    case FRONT + RIGHT:
      motors.turnLeft();
      break;
    case FRONT + LEFT:
      motors.turnRight();
      break;
    case RIGHT + LEFT:
      motors.traverseCell();
      break;
    case FRONT + RIGHT + LEFT:
      motors.turnAround();
      break;
    default:
      Serial1.println("Error: Default");
      motors.halt();
      blink(1);
      break;
  }
}
