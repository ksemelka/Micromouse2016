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



void executeStack(){    //after hitting U-Turn,
  byte topCommand = navHistory.top();
  while (topCommand < 8){   //While not random variable do same movements except turn right for Left and turn left for Right

    if (topCommand == 1){   //For Forward go forward
      motors.traverseCell();
      navHistory.pop();
    }

    if (topCommand == 2){     //For Right go left
      motors.turnLeft();
      navHistory.pop();
    }

    if (topCommand == 4){    //For Left go right
      motors.turnRight();
      navHistory.pop();
    }
    topCommand = navHistory.top();
  }

  if (topCommand == 8){     //if you randomly chose to go forward, now randomly choose between left and right

  }


  if (topCommand == 16){     //if you randomly chose to go forward, now randomly choose between left and right

  }


  if (topCommand == 32{     //if you randomly chose to go forward, now randomly choose between left and right

  }

  if (topCommand == 64){
    if (random(millis() % 2)) {
      navHistory.push(32);
      motors.traverseCell();
    }
    else {
      navHistory.push(32);
      delay(200);
      motors.turnLeft();
      delay(200);
      motors.traverseCell();
    }
  }
}

//Forward       1
//Right         2
//Left          4
//RandomLR       8         (Left Right Option)
//RandomFL       16        (Front Left Option)
//RandomFR       32        (Front Right Option)
//RandomFLR       64        (3 options)

void navigate() {
  printState();

  switch (state()) {
    case 0:                            // RANDOM D: Randomly choose left, right, or straight
    if (random(millis()) % 3 == 2) {  //Random D and it chose Right
      navHistory.push(2)                //CHECK   Turn Right
      navHistory.push(64)               //CHECK   RandomD
      navHistory.push(1);

      delay(200);
      motors.turnRight();
      delay(200);
      motors.traverseCell();
    }
    else if (random(millis()) % 3 == 1) {     //Random and it chose Left
      navHistory.push(4);                //CHECK   Turn left
      navHistory.push(64);               //CHECK   Random D
      navHistory.push(1);
      delay(200);
      motors.turnLeft();
      delay(200);
      motors.traverseCell();
    }
    else {                                  //Random and it "chose" Forward
      navHistory.push(1)                //forward
      navHistory.push(64)               //RandomD

      motors.traverseCell()
    }
    break;

    case FRONT:                   //Random A: WALL IS ONLY IN FRONT
      if (random(millis()) % 2) {          //RANDOM: Turn Left
      navHistory.push(4)                //CHECK   add Left Turn followed by Random indicator to stack
      navHistory.push(8)               //CHECK

        delay(200);
        motors.turnLeft();
        delay(200);

        navHistory.push(1)                //CHECK Add Forward to stack

        motors.traverseCell();
      }

      else {                        //RANDOM: Turn Right
      navHistory.push(2)                //CHECK   add Right followed by
      navHistory.push(8)               //CHECK    Random A

        delay(200);
        motors.turnRight();

        navHistory.push(1)                //CHECK Add Forward to stack

        delay(200);
        motors.traverseCell();
      }
      break;


    case RIGHT:                     //Random B: Turn left or go forward randomly
      if (random(millis()) % 2) {   // Randomly chose left
      navHistory.push(4)                //Add Left to stack
      navHistory.push(16)               //Add Random B to stack

       delay(200);
       motors.turnLeft();

        navHistory.push(1)                //Add Forward to stack

       delay(200);
       motors.traverseCell();
      }


      else {                               //Randomly chose forward
        navHistory.push(1)
        navHistory.push(16)                //CHECK Add Forward to stack
        motors.traverseCell();
      }
      break;


    case LEFT:                      //Random C: Choose forward or right
      if (random(millis()) % 2) {   // chose Right
      navHistory.push(2)                //CHECK Add Right to stack
      navHistory.push(32)

       delay(200);
       motors.turnRight();

       navHistory.push(1)                //CHECK Add Forward to stack
       delay(200);
       motors.traverseCell();
      }
      else {                     //Chose Forward
        navHistory.push(1)               //Add forward to stack
        navHistory.push(32)             //Add random C to stack
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
