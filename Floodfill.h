#ifndef FLOODFILL_H
#define FLOODFILL_H


bool outOfBounds(int);
void pushSelfAndAdjacentCells(int x, int y);
void floodfill();
void analyzePosition();

#endif /*FLOODFILL_H*/
