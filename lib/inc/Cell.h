/*
Andrew Nava-Juarez
anava014@ucr.edu
*/

#ifndef CELL_H
#define CELL_H

#include "Wall.h"
#include "Arduino.h"
//#include <iostream>
// #include <string>
using namespace std;

class Cell{
private:
  Wall northWall;
  Wall southWall;
  Wall eastWall;
  Wall westWall;

  int xCoor;
  int yCoor;

  int distance;

  bool hasTraversed;
  bool efficiencyTraversed;

  String cellDrawing;

  void fillTop();
  void fillLeftRight();
  void fillBottom();
  bool liveMouse;

public:
  Cell();
  Cell(bool north, bool south, bool east, bool west);
  // void printCell();
  bool wallStatus(String direction);
  bool wallStatus(int facing);
  void setWall(String direction);
  void setMouseInCell();
  void removeMouseInCell();
  void setDistance(int d);
  String returnDistance();
  int returnIntDistance();
  void setCoordinates(int x, int y);

  void setTraversed();
  bool returnHasTraversed(){
    return hasTraversed;
  }

  void setEffTraversed();
  bool returnHasEffTraversed(){
    return efficiencyTraversed;
  }

  int returnXCoor();
  int returnYCoor();
};

#endif
