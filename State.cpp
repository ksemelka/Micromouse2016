#include "State.h"
#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
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



void executeStack(){    //after hitting U-Turn, go through stack, from top, doing same movements except turn right for Left and turn left for Right
  while (navHistory.top() !=


  if (navHistory.top())== 1){
  motors.traverseCell();
  navHistory.pop();
}
  if (navHistory.top())== 2){
  motors.turnLeft();
  navHistory.pop();
}
  if (navHistory.top())== 4);{
  motors.turnRight();
  navHistory.pop();
}

if (navHistory.top() == 8){     //if you randomly chose to go forward, now randomly choose between left and right

}


if (navHistory.top() == 16){     //if you randomly chose to go forward, now randomly choose between left and right

}


if (navHistory.top() == 32{     //if you randomly chose to go forward, now randomly choose between left and right

}


//Forward       1
//Right         2
//Left          4
//RandomA       8         (Left Right Option)
//RandomB       16        (Front Left Option)
//RandomC       32        (Front Left Option)
//RandomD       64        (3 options)

void navigate() {
  printState();

  switch (state()) {
    case 0:                            // RANDOM D: Randomly choose left, right, or straight
    if (random(millis()) % 3 == 2) {
      navHistory.push(2)                //CHECK   add Right Turn in a Random D situation
      navHistory.push(16)               //CHECK
      delay(200);
      motors.turnRight();
      delay(200);
    }
    else if (random(millis()) % 3 == 1) {
      navHistory.push(4)                //CHECK   add Left Turn followed by Random indicator to stack
      navHistory.push(16)               //CHECK
      delay(200);
      motors.turnLeft();
      delay(200);
    }

    navHistory.push(1)                //CHECK   add Forward followed by Random indicator to stack
    navHistory.push(16)               //CHECK
    motors.traverseCell();

    break;

    case FRONT:                   //WALL IS ONLY IN FRONT
      if (random(millis()) % 2) {          //RANDOM: Turn left or right randomly
      navHistory.push(4)                //CHECK   add Left Turn followed by Random indicator to stack
      navHistory.push(16)               //CHECK

        delay(200);
        motors.turnLeft();
        delay(200);

        navHistory.push(1)                //CHECK Add Forward to stack

        motors.traverseCell();
      }
      else {
      navHistory.push(2)                //CHECK   add Right followed by Random indicator to stack
      navHistory.push(16)               //CHECK

        delay(200);
        motors.turnRight();

        navHistory.push(1)                //CHECK Add Forward to stack

        delay(200);
        motors.traverseCell();
      }
      break;


    case RIGHT:
      if (random(millis()) % 2) {   // Turn left or go forward randomly
      navHistory.push(4)                //CHECK Add Left to stack

       delay(200);
       motors.turnLeft();

        navHistory.push(1)                //CHECK Add Forward to stack

       delay(200);
       motors.traverseCell();
      }


      else {
        navHistory.push(1)                //CHECK Add Forward to stack
        motors.traverseCell();
      }
      break;

    case LEFT:
      if (random(millis()) % 2) {   // Turn right or go forward randomly
      navHistory.push(2)                //CHECK Add Right to stack

       delay(200);
       motors.turnRight();

       navHistory.push(1)                //CHECK Add Forward to stack
       delay(200);
       motors.traverseCell();
      }
      else {
        navHistory.push(1)               //CHECK
        motors.traverseCell();
      }
      break;

    case FRONT + RIGHT:
      motors.brake();
      delay(200);

      navHistory.push(4)               //CHECK
      motors.turnLeft();
      delay(200);
      navHistory.push(1)               //CHECK
      motors.traverseCell();
      break;

    case FRONT + LEFT:
      motors.brake();
      delay(200);
      navHistory.push(2)               //CHECK
      motors.turnRight();
      delay(200);
      navHistory.push(1)               //CHECK
      motors.traverseCell();
      break;

    case RIGHT + LEFT:
      navHistory.push(1)               //CHECK
      motors.traverseCell();
      break;

    case FRONT + RIGHT + LEFT:
      motors.brake();
      delay(50);
      motors.turnAround();
      delay(200);
      executeStack();               //Check
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
