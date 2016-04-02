#ifndef STATE_H
#define STATE_H
#include <Arduino.h>
#include "Sensors.h"

#define FRONT 1
#define RIGHT 2
#define LEFT 4

// Values for how far the mouse should be from walls
const int targetFront = 400;
const int thresholdFront = 100;
const int targetSide = analogRead(rightPT);   // FIXME: Target side being too high might be what
                                              //          is causing it to not go straight
const int thresholdSide = 80;

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
