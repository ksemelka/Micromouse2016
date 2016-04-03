#ifndef STATE_H
#define STATE_H
#include "Sensors.h"
#include <Arduino.h>

#define FRONT 1
#define RIGHT 2
#define LEFT 4

// Values for how far the mouse should be from walls
const int targetFront = 460;      // stopping value
const int thresholdFront = 120;   // reading value to indicate wall
const int thresholdSide = 120;     // reading value to indicate if there is a wall

bool wallToTheFront();
bool wallToTheRight();
bool wallToTheLeft();
byte state();
void printState();
void navigate();

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
