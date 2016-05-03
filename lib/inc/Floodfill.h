#ifndef FLOODFILL_H
#define FLOODFILL_H
#include "Cell.h"
#include "Maze.h"
#include "CellStack.h"

bool outOfBounds(int);
void pushSelfAndAdjacentCells(int x, int y);
void floodfill();
void analyzePosition();
int returnIncrementedFacing();
int returnDecrementedFacing();
extern int facing;
extern CellStack floodStack;
void step();

#endif /*FLOODFILL_H*/
