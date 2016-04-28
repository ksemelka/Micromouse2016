#include "State.h"
#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "pwm.h"
#include <Arduino.h>

extern Motors motors;
extern Sensors sensors;

bool wallToTheFront() {
  if (sensors.frontPTReading > thresholdFront) {
    return true;
  }
  return false;
}

bool wallToTheRight() {
  if (sensors.rightPTReading > thresholdSide) {
    return true;
  }
  return false;
}

bool wallToTheLeft() {
  if (sensors.leftPTReading > thresholdSide) {
    return true;
  }
  return false;
}

byte state() {
  byte currentState = 0;
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
    case 0:       // Randomly choose left, right, or straight
    if (random(millis()) % 3 == 2) {
      delay(200);
      motors.turnRight();
      delay(200);
    }
    else if (random(millis()) % 3 == 1) {
      delay(200);
      motors.turnLeft();
      delay(200);
    }
    motors.traverseCell();
    break;
    case FRONT:
      if (random(millis()) % 2) {   // Turn left or right randomly
        delay(200);
        motors.turnLeft();
        delay(200);
        motors.traverseCell();
      }
      else {
        delay(200);
        motors.turnRight();
        delay(200);
        motors.traverseCell();
      }
      break;
    case RIGHT:
      if (random(millis()) % 2) {   // Turn left or go forward randomly
       delay(200);
       motors.turnLeft();
       delay(200);
       motors.traverseCell();
      }
      else {
        motors.traverseCell();
      }
      break;
    case LEFT:
      if (random(millis()) % 2) {   // Turn right or go forward randomly
       delay(200);
       motors.turnRight();
       delay(200);
       motors.traverseCell();
      }
      else {
        motors.traverseCell();
      }
      break;
    case FRONT + RIGHT:
      motors.brake();
      delay(200);
      motors.turnLeft();
      delay(200);
      motors.traverseCell();
      break;
    case FRONT + LEFT:
      motors.brake();
      delay(200);
      motors.turnRight();
      delay(200);
      motors.traverseCell();
      break;
    case RIGHT + LEFT:
      motors.traverseCell();
      break;
    case FRONT + RIGHT + LEFT:
      motors.brake();
      delay(50);
      motors.turnAround();
      delay(200);
      motors.traverseCell();
      break;
    default:
      Serial1.println("Error: Default");
      motors.halt();
      blink(1);
      break;
  }
}

void solveRightHand() {
  printState();
  switch (state()) {
    case 0:
      motors.turnRight();
      delay(100);
      motors.traverseCell();
      break;
    case FRONT:
        motors.turnRight();
        delay(200);
        motors.traverseCell();
      break;
    case RIGHT:
        motors.traverseCell();
      break;
    case LEFT:
       motors.turnRight();
       delay(200);
       motors.traverseCell();
      break;
    case FRONT + RIGHT:
      motors.turnLeft();
      delay(200);
      motors.traverseCell();
      break;
    case FRONT + LEFT:
      motors.turnRight();
      delay(200);
      motors.traverseCell();
      break;
    case RIGHT + LEFT:
      motors.traverseCell();
      break;
    case FRONT + RIGHT + LEFT:
      motors.turnAround();
      delay(300);
      motors.traverseCell();
      break;
    default:
      Serial1.println("Error: Default");
      motors.halt();
      blink(1);
      break;
  }
}
