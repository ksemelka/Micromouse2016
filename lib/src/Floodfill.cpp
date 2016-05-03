#include "../inc/Floodfill.h"
#include "../inc/Cell.h"
#include "../inc/Sensors.h"
#include "../inc/State.h"
#include "../inc/pwm.h"
#include "../inc/Buzzer.h"

int facing = 0;

extern Sensors sensors;
Cell liveMaze[16][16];
CellStack floodStack;

int returnIncrementedFacing(){
  if (facing == 3){
     return 0;
  }
  return facing + 1;

}

int returnDecrementedFacing(){
  if (facing == 0){
    return 3;
  }
  return facing-1;

}

bool outOfBounds(int x){
  if(x < 0 || x > 15)
    return true;
  return false;
}

void pushSelfAndAdjacentCells(int x, int y){
  for(int i = y + 1; i >= y - 1; --i){
    for(int j = x + 1; j >= x - 1; --j){
      if(!outOfBounds(j) && !outOfBounds(i))
        floodStack.push(liveMaze[j][i]);
    }
  }
}

void floodfill(){
  bool pushingCells = false;
  if (wallToTheRight()) {
//      &&   // if there is NO WALL on east
//        !liveMaze[xPos][yPos].wallStatus(returnIncrementedFacing())){
        setNewWall(returnIncrementedFacing(), xPos, yPos);
        pushingCells = true;
//        playTone(2000, 200);
  }
  if (wallToTheLeft()) {
//  &&   // if there is NO WALL on west
//        !liveMaze[xPos][yPos].wallStatus(returnDecrementedFacing())){
        setNewWall(returnDecrementedFacing(), xPos, yPos);
        pushingCells = true;
//        playTone(1400, 200);
  }
  if (wallToTheFront()) {
//  &&   // if there is NO WALL on north
//        !liveMaze[xPos][yPos].wallStatus(facing)){
        setNewWall(facing, xPos, yPos);
        pushingCells = true;
//        playTone(500, 200);

  }
  if(pushingCells)
    pushSelfAndAdjacentCells(xPos, yPos);

  Serial1.print("xPos: ");
  Serial1.println(xPos);
  Serial1.print("yPos: ");
  Serial1.println(yPos);

  while(!floodStack.isEmpty()){
    Cell cellCheck = floodStack.pop();

    int minDistance = 99;
    //Grabbing Minimum Distance
    for(int i = 0; i < 4; ++i){
      if(!cellCheck.wallStatus(i)){
        if(i == 0 && !outOfBounds(cellCheck.returnXCoor() + 1)){
          int cellDistance = liveMaze[cellCheck.returnXCoor() + 1]
          [cellCheck.returnYCoor()].returnIntDistance();
          if(cellDistance <= minDistance)
            minDistance = cellDistance;
        }
        else if(i == 1 && !outOfBounds(cellCheck.returnYCoor() - 1)){
          int cellDistance = liveMaze[cellCheck.returnXCoor()]
          [cellCheck.returnYCoor() - 1].returnIntDistance();
          if(cellDistance <= minDistance)
            minDistance = cellDistance;
        }
        else if(i == 2 && !outOfBounds(cellCheck.returnXCoor() - 1)){
          int cellDistance = liveMaze[cellCheck.returnXCoor() - 1]
          [cellCheck.returnYCoor()].returnIntDistance();
          if(cellDistance <= minDistance)
            minDistance = cellDistance;
        }
        else if(i == 3 && !outOfBounds(cellCheck.returnYCoor() + 1)){
          int cellDistance = liveMaze[cellCheck.returnXCoor()]
          [cellCheck.returnYCoor() + 1].returnIntDistance();
          if(cellDistance <= minDistance)
            minDistance = cellDistance;
        }
      }
    }
    //The distance of currCell should be the minimum open neighbor + 1
    //If not, set that value and push all open neighbors to stack
    if(cellCheck.returnIntDistance() != 0 &&
      cellCheck.returnIntDistance() != minDistance + 1){
      liveMaze[cellCheck.returnXCoor()][cellCheck.returnYCoor()].
      setDistance(minDistance + 1);

      //Pushing all open neighbors to stack
      for(int i = 0; i < 4; ++i){
        if(!cellCheck.wallStatus(i)){
          if(i == 0 && !outOfBounds(cellCheck.returnXCoor() + 1)){
            floodStack.push(liveMaze[cellCheck.returnXCoor() + 1]
              [cellCheck.returnYCoor()]);
          }
          else if(i == 1 && !outOfBounds(cellCheck.returnYCoor() - 1)){
            floodStack.push(liveMaze[cellCheck.returnXCoor()]
              [cellCheck.returnYCoor() - 1]);
          }
          else if(i == 2 && !outOfBounds(cellCheck.returnXCoor() - 1)){
            floodStack.push(liveMaze[cellCheck.returnXCoor() - 1]
              [cellCheck.returnYCoor()]);
          }
          else if(i == 3 && !outOfBounds(cellCheck.returnYCoor() + 1)){
            floodStack.push(liveMaze[cellCheck.returnXCoor()]
              [cellCheck.returnYCoor() + 1]);
          }
        }
      }
    }
  }
}

void analyzePosition(){
  int minDistance = 99;
  int minPosition = -1;
  //Grabbing Minimum Distance
  liveMaze[xPos][yPos].setTraversed();
  for(int i = 0; i < 4; ++i){
    if(!liveMaze[xPos]
        [yPos].wallStatus(i)){

      if(i == 0){
        int cellDistance = liveMaze[xPos + 1]
        [yPos].returnIntDistance();

        if(!liveMaze[xPos+1][yPos].returnHasTraversed() && cellDistance <= minDistance){
          minDistance = cellDistance;
          minPosition = i;
        }
      }
      else if(i == 1){
        int cellDistance = liveMaze[xPos]
        [yPos - 1].returnIntDistance();
        if(!liveMaze[xPos][yPos - 1].returnHasTraversed() && cellDistance <= minDistance){
          minDistance = cellDistance;
          minPosition = i;
        }
      }
      else if(i == 2){
        int cellDistance = liveMaze[xPos - 1]
        [yPos].returnIntDistance();
        if(!liveMaze[xPos-1][yPos].returnHasTraversed() && cellDistance <= minDistance){
          minDistance = cellDistance;
          minPosition = i;
        }
      }
      else if(i == 3){
        int cellDistance = liveMaze[xPos]
        [yPos + 1].returnIntDistance();
        if(!liveMaze[xPos][yPos + 1].returnHasTraversed() && cellDistance <= minDistance){
          minDistance = cellDistance;
          minPosition = i;
        }
      }
    }
  }

  if(minPosition == -1){ //Second Check Since There is no cheaper solution
    for(int i = 0; i < 4; ++i){
      if(!liveMaze[xPos][yPos].wallStatus(i)){

        if(i == 0){
          int cellDistance = liveMaze[xPos + 1][yPos].returnIntDistance();

          if(cellDistance <= minDistance){
            minDistance = cellDistance;
            minPosition = i;
          }
        }
        else if(i == 1){
          int cellDistance = liveMaze[xPos][yPos - 1].returnIntDistance();
          if(cellDistance <= minDistance){
            minDistance = cellDistance;
            minPosition = i;
          }
        }
        else if(i == 2){
          int cellDistance = liveMaze[xPos - 1][yPos].returnIntDistance();
          if(cellDistance <= minDistance){
            minDistance = cellDistance;
            minPosition = i;
          }
        }
        else if(i == 3){
          int cellDistance = liveMaze[xPos][yPos + 1].returnIntDistance();
          if(cellDistance <= minDistance){
            minDistance = cellDistance;
            minPosition = i;
          }
        }
      }
    }
  }

//  if(minPosition == -1){    //ERROR SAFEGAURD
//      halt();
//      tone(speaker, 500);
//      delay(1000);
//      mode = 1;
//      noTone(speaker);
//  }
//while(!Serial1.available()){}
//Serial1.read();
  //Turn mouse here
  if(facing == 0){
    if(minPosition == 0){}      //do Nothing

    else if(minPosition == 1){
      turnRightEncoderTicks();
    }
    else if(minPosition == 2){
      turnRightEncoderTicks();      //U TURN
      turnRightEncoderTicks();
    }
    else if(minPosition == 3){
      turnLeftEncoderTicks();
    }
  }

  else if(facing == 1){
    if(minPosition == 0)
      turnLeftEncoderTicks();
    else if(minPosition == 1){}
      //do nothing
    else if(minPosition == 2){
      turnRightEncoderTicks();
    }
    else if(minPosition == 3){
      turnRightEncoderTicks();      //U TURN
      turnRightEncoderTicks();
    }
  }
  else if(facing == 2){
    if(minPosition == 0){
      turnRightEncoderTicks();      //U TURN
      turnRightEncoderTicks();
    }
    else if(minPosition == 1)
      turnLeftEncoderTicks();
    else if(minPosition == 2){}      //do nothing
    else if(minPosition == 3){
      turnRightEncoderTicks();
    }
  }
  else if(facing == 3){
    if(minPosition == 0)
      turnRightEncoderTicks();
    else if(minPosition == 1){
      turnRightEncoderTicks();
      turnRightEncoderTicks();
    }
    else if(minPosition == 2){
      turnLeftEncoderTicks();
    }
    else if(minPosition == 3){}
      //do nothing
  }
  facing = minPosition;
}

void step() {
  goForwardDist(ONECELLDISTANCE);
  switch(facing) {
    case 0:
      xPos++;
      break;
    case 1:
      yPos--;
      break;
    case 2:
      xPos--;
      break;
    case 3:
      yPos++;
      break;
  }
}
