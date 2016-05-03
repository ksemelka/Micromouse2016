/*
Andrew Nava-Juarez
anava014@ucr.edu
*/

#include "../inc/Cell.h"
#include "../inc/Maze.h"

Cell :: Cell(){
  cellDrawing = "";
  hasTraversed = false;
  distance = -1;

  northWall.markNotPresent();
  southWall.markNotPresent();
  eastWall.markNotPresent();
  westWall.markNotPresent();

  fillTop();
  fillLeftRight();
  fillBottom();
}

Cell :: Cell(bool north, bool south, bool east, bool west){
  cellDrawing = "";
  hasTraversed = false;

  (north) ? (northWall.markPresent()) : (northWall.markNotPresent());
  (south) ? (southWall.markPresent()) : (southWall.markNotPresent());
  (east) ? (eastWall.markPresent()) : (eastWall.markNotPresent());
  (west) ? (westWall.markPresent()) : (westWall.markNotPresent());

  fillTop();
  fillLeftRight();
  fillBottom();
}

void Cell :: setMouseInCell(){
  liveMouse = true;
}

void Cell :: removeMouseInCell(){
  liveMouse = false;
}

void Cell :: setWall(String direction){
  if(direction == "north")
    northWall.markPresent();
  else if(direction == "south")
    southWall.markPresent();
  else if(direction == "east")
    eastWall.markPresent();
  else if(direction == "west")
    westWall.markPresent();
}

bool Cell :: wallStatus(String direction){
  if(direction == "north")
    return northWall.returnIsPresent();
  else if(direction == "south")
    return southWall.returnIsPresent();
  else if(direction == "east")
    return eastWall.returnIsPresent();
  else if(direction == "west")
    return westWall.returnIsPresent();
  //cout << endl << "ERROR: Reached end of wallStatus in Cell.cpp" << endl;
  return false;
}

bool Cell :: wallStatus(int facing){
  if(facing == 0)
    return northWall.returnIsPresent();
  else if(facing == 2)
    return southWall.returnIsPresent();
  else if(facing == 1)
    return eastWall.returnIsPresent();
  else if(facing == 3)
    return westWall.returnIsPresent();
  //cout << endl << "ERROR: Reached end of wallStatus in Cell.cpp" << endl;
  return false;
}

void Cell :: fillTop(){
  if(northWall.returnIsPresent())
    cellDrawing += "+---+\n";
  else
    cellDrawing += "+   +\n";
}

void Cell :: fillLeftRight(){
  if(eastWall.returnIsPresent() && westWall.returnIsPresent())
    cellDrawing += "|   |\n";
  else if(!eastWall.returnIsPresent() && westWall.returnIsPresent())
    cellDrawing += "|    \n";
  else if(eastWall.returnIsPresent() && !westWall.returnIsPresent())
    cellDrawing += "    |\n";
  else
    cellDrawing += "     \n";
}

void Cell :: setCoordinates(int x, int y){
  xCoor = x;
  yCoor = y;
}

int Cell :: returnXCoor(){
  return xCoor;
}

int Cell :: returnYCoor(){
  return yCoor;
}

void Cell :: fillBottom(){
  if(southWall.returnIsPresent())
    cellDrawing += "+---+";
  else
    cellDrawing += "+   +";
}

void Cell :: setDistance(int d){
  distance = d;

}

void Cell :: setTraversed(){
  hasTraversed = true;
}

void Cell :: setEffTraversed(){
  efficiencyTraversed = true;
}

String Cell :: returnDistance(){
  if(distance == -1)
    return "-1";
  else if(distance >= 0 && distance <=9)
    return " " + String(distance);
  else
    return String(distance);
}

int Cell :: returnIntDistance(){
  return distance;
}

// void Cell :: printCell(){
//  cout << cellDrawing;
// }
