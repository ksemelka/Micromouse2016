#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"


extern int xPos;
extern int yPos;
extern Cell liveMaze[][16];


void setNewWall(int, int, int);
void setLiveEastWestWalls(int, int);
void mazeSetup();
void printLiveMaze();

#endif /*MAZE_H*/
