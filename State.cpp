#include "State.h"
#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include <Arduino.h>
#include <stack>


std::stack <byte> navHistory;

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
  turnLEDOn();
  while (navHistory.top() < 8){   //While not random variable do same movements except turn right for Left and turn left for Right

    if (navHistory.top()== 1){   //For Forward go forward
      motors.traverseCell();
      navHistory.pop();
      }

    if (navHistory.top()== 2){     //For Right go left
      delay(200);
      motors.turnLeft();
      delay(200);
      navHistory.pop();
      }

    if (navHistory.top()== 4){    //For Left go right
      delay(200);
      motors.turnRight();
      delay(200);
      navHistory.pop();
      }
  }
//RANDOM THINGS of Execute
    if (navHistory.top() == 8){     //LR opening; if you went left last time, go forward this time
                                    //            if you went right last time, go forward this time
      navHistory.pop();        //pop the Random8 indicator

        navHistory.pop();     //despite being right or left, for LR intersections go forward
        motors.traverseCellStack();
      }


    else if (navHistory.top() == 16){     //Random Front Left options
      navHistory.pop();
      if (navHistory.top() == 4){   //if you random chose Left
        navHistory.pop();
        delay(200);
        motors.turnLeftStack();    //go left
        delay(200);
      }

      else if (navHistory.top() == 1){ //if you random chose Straight
        navHistory.pop();
        delay(200);
        motors.turnRightStack();  //go right
        delay(200);
      }
    }

    else if (navHistory.top() == 32){  //Random Front Right options
      navHistory.pop();
      if (navHistory.top() == 2){ //if you random chose right
      navHistory.pop();
      delay(200);
      motors.turnRightStack();  //go right
      delay(200);
      }

      else if (navHistory.top() == 1){ //if you random chose forward
        navHistory.pop();
        delay(200);
        motors.turnLeftStack(); //go left
        delay(200);
      }
    }

    else if (navHistory.top() == 64){
      navHistory.pop();
      if (navHistory.top() == 1){ //if you random chose Forward
        navHistory.pop();
        if (random(millis()) % 2) {          //Randomly choose between L and R
          delay(200);
          motors.turnLeftStack();
          delay(200);
        }
        else {
          delay(200);
          motors.turnRightStack();
          delay(200);
        }
      }

      else if (navHistory.top() == 2){ //if you random chose Right
        navHistory.pop();
        if (random(millis()) % 2) {          //Randomly choose between F and R
          delay(200);
          motors.turnRightStack();
          delay(200);
        }
        else {
          motors.traverseCellStack();
        }
      }

      else if (navHistory.top() == 4){ //if you random chose Left
        navHistory.pop();
        if (random(millis()) % 2) {          //Randomly choose between F and L
          delay(200);
          motors.turnLeftStack();
          delay(200);
        }
        else {
          motors.traverseCellStack();
        }
      }
    }
    turnLEDOff();
}
    //Forward       1
    //Right         2
    //Left          4
    //RandomA       8         (Left Right Option)
    //RandomB       16        (Front Left Option)
    //RandomC       32        (Front Right Option)
    //RandomD       64        (3 options)

void navigateStack(){
      printState();

      switch (state()) {
        case 0:                            // RANDOM D: Randomly choose left, right, or straight
        if (random(millis()) % 3 == 2) {  //Random D and it chose Right
          delay(200);
          motors.turnRightStack();
          navHistory.push(64);               //CHECK   RandomD
          delay(200);

          motors.traverseCellStack();
        }

        else if (random(millis()) % 3 == 1) {     //Random and it chose Left
          delay(200);
          motors.turnLeftStack();
          navHistory.push(64);               //CHECK   Random D
          delay(200);

          motors.traverseCellStack();
        }

        else {                                  //Random and it "chose" Forward
          motors.traverseCellStack();
          navHistory.push(64);               //RandomD
        }
    //    navHistory.push(16)               //CHECK



        break;

        case FRONT:                   //Random A: WALL IS ONLY IN FRONT
          if (random(millis()) % 2) {          //RANDOM: Turn Left

            delay(200);
            motors.turnLeftStack();
            navHistory.push(8);
            delay(200);

            motors.traverseCellStack();
          }

          else {                        //RANDOM: Turn Right

            delay(200);
            motors.turnRightStack();
            navHistory.push(8);               //CHECK    Random A

            delay(200);
            motors.traverseCellStack();
          }
          break;


        case RIGHT:   //Random LF              //Random B: Turn left or go forward randomly
          if (random(millis()) % 2) {   // Randomly chose left

           delay(200);
           motors.turnLeftStack();
           navHistory.push(16);               //Add Random B to stack

           delay(200);
           motors.traverseCellStack();
          }


          else {                               //Randomly chose forward
            motors.traverseCellStack();
            navHistory.push(16);                //CHECK Add Forward to stack
          }
          break;


        case LEFT:                      //Random C: Choose forward or right
          if (random(millis()) % 2) {   // chose Right


           delay(200);
           motors.turnRightStack();
           navHistory.push(32);
           delay(200);
           motors.traverseCellStack();
          }

          else {                     //Chose Forward
            motors.traverseCellStack();
            navHistory.push(32);             //Add random C to stack
          }
          break;

    //NON RANDOM CASES V V V
        case FRONT + RIGHT:
          motors.brake();
          delay(200);

          motors.turnLeft();
          delay(200);
          motors.traverseCellStack();
          break;

        case FRONT + LEFT:
          motors.brake();
          delay(200);
          motors.turnRightStack();
          delay(200);
          motors.traverseCellStack();
          break;

        case RIGHT + LEFT:
          motors.traverseCellStack();
          break;

        case FRONT + RIGHT + LEFT:
          motors.brake();
          delay(50);
          motors.turnAround();
          delay(200);
          executeStack();               //Check
          motors.traverseCellStack();
          break;
        default:
          Serial1.println("Error: Default");
          motors.halt();
          blink(1);
          break;
      }

}


//ORIGINAL NAVIGATE
void navigate() {
  printState();

  switch (state()) {
    case 0:                            // RANDOM D: Randomly choose left, right, or straight
    if (random(millis()) % 3 == 2) {  //Random D and it chose Right
      delay(200);
      motors.turnRight();
      delay(200);
    }

    else if (random(millis()) % 3 == 1) {     //Random and it chose Left
      delay(200);
      motors.turnLeft();
      delay(200);
    }

    motors.traverseCell();

    break;

    case FRONT:                   //Random A: WALL IS ONLY IN FRONT
      if (random(millis()) % 2) {          //RANDOM: Turn Left


        delay(200);
        motors.turnLeft();
        delay(200);

        motors.traverseCell();
      }

      else {                        //RANDOM: Turn Right

        delay(200);
        motors.turnRight();


        delay(200);
        motors.traverseCell();
      }
      break;


    case RIGHT:                     //Random B: Turn left or go forward randomly
      if (random(millis()) % 2) {   // Randomly chose left

       delay(200);
       motors.turnLeft();


       delay(200);
       motors.traverseCell();
      }


      else {                               //Randomly chose forward
        motors.traverseCell();
      }
      break;


    case LEFT:                      //Random C: Choose forward or right
      if (random(millis()) % 2){   // chose Right

       delay(200);
       motors.turnRight();

       delay(200);
       motors.traverseCell();
      }
      else {                     //Chose Forward

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
