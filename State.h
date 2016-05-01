#ifndef STATE_H
#define STATE_H
#include "Sensors.h"
#include <Arduino.h>

#define FRONT 1
#define RIGHT 2
#define LEFT 4

// Values for how far the mouse should be from walls
extern int targetFront;      // stopping value
extern int targetRight;
extern int targetLeft;
extern int thresholdFront;   // reading value to indicate wall
extern int thresholdSide;     // reading value to indicate if there is a wall

bool wallToTheFront();
bool wallToTheRight();
bool wallToTheLeft();
byte state();
void printState();
void navigate();
void solveRightHand();
void newNavigate();
void newSolveRightHand();

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
