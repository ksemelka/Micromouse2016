#include "../inc/Maze.h"

int xPos = 0;
int yPos = 0;

void mazeSetup(){
  xPos = 0;
  yPos = 15;
  int j = 15;
  for(int i = 0; i < 16; ++i){
    liveMaze[i][j].setWall("west"); //[k][15]
  }
  int i = 0;
  for(int j = 0; j < 16; ++j){
    liveMaze[i][j].setWall("south"); //[0][k]
  }
  j = 0;
  for(int i = 0; i < 16; ++i){
    liveMaze[i][j].setWall("east");//[k][0]
  }
  i = 15;
  for(int j = 0; j < 16; ++j){
    liveMaze[i][j].setWall("north");//[15][k]
  }

  setLiveEastWestWalls(0,14); //Starting Cell
  //distances
  liveMaze[7][7].setDistance(0);
  liveMaze[7][8].setDistance(0);
  liveMaze[8][7].setDistance(0);
  liveMaze[8][8].setDistance(0);

  for(int x = 0; x < 16; ++x){
    for(int y = 0; y < 16; ++y){
      liveMaze[x][y].setCoordinates(x, y);
    }
  }


  for(int x = 0; x < 16; ++x){
    for(int y = 0; y < 16; ++y){
      if(x < 8 && y < 8)
        liveMaze[x][y].setDistance(abs(7 - x) + abs(7 - y));
      else if(x < 8 && y >= 8)
        liveMaze[x][y].setDistance(abs(7 - x) + abs(8 - y));
      else if(x >= 8 && y >= 8)
        liveMaze[x][y].setDistance(abs(8 - x) + abs(8 - y));
      else if(x >= 8 && y < 8)
        liveMaze[x][y].setDistance(abs(8 - x) + abs(7 - y));
    }
  }
}

void setLiveEastWestWalls(int up, int left){
  if(left != 15)
    liveMaze[up][left + 1].setWall("east");
  liveMaze[up][left].setWall("west");
}

void setLiveNorthSouthWalls(int up, int left){
  liveMaze[up][left].setWall("north");
  liveMaze[up + 1][left].setWall("south");
}

void printLiveMaze(){
  for(int i = 15; i >= 0; --i){
    for(int j = 15; j >= 0; --j){
      if(liveMaze[i][j].wallStatus("north"))
        Serial1.print("+---+");
      else
        Serial1.print("+   +");
    }
    Serial1.println();
    for(int j = 15; j >= 0; --j){
      if(xPos == i && yPos == j){
        if(liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
        Serial1.print("|" + liveMaze[i][j].returnDistance() + "*" + "|");
      else if(!liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
        Serial1.print("|" + liveMaze[i][j].returnDistance() + "*" + " ");
      else if(liveMaze[i][j].wallStatus("east") && !liveMaze[i][j].wallStatus("west"))
        Serial1.print(" " + liveMaze[i][j].returnDistance() + "*" + "|");
      else
        Serial1.print(" " + liveMaze[i][j].returnDistance() + "*" + " ");
      }
      else {
        if(liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
          Serial1.print("|" + liveMaze[i][j].returnDistance() + " |");
        else if(!liveMaze[i][j].wallStatus("east") && liveMaze[i][j].wallStatus("west"))
          Serial1.print("|" + liveMaze[i][j].returnDistance() + "  ");
        else if(liveMaze[i][j].wallStatus("east") && !liveMaze[i][j].wallStatus("west"))
          Serial1.print(" " + liveMaze[i][j].returnDistance() + " |");
        else
          Serial1.print(" " + liveMaze[i][j].returnDistance() + "  ");
      }
    }
    Serial1.println();
    for(int j = 15; j >= 0; --j){
      if(liveMaze[i][j].wallStatus("south"))
        Serial1.print("+---+");
      else
        Serial1.print("+   +");
    }
    Serial1.println();
  }
  Serial1.println();
  Serial1.print("xPos: ");
  Serial1.println(xPos);
  Serial1.print("yPos: ");
  Serial1.println(yPos);
}

void setNewWall(int wallDirection, int x, int y){
  if(wallDirection == 0)
    setLiveNorthSouthWalls(x, y);
  else if(wallDirection == 1)
    setLiveEastWestWalls(x, y-1);
  else if(wallDirection == 2)
    setLiveNorthSouthWalls(x-1, y);
  else if(wallDirection == 3)
    setLiveEastWestWalls(x, y);
}
