/*
Andrew Nava-Juarez
anava014@ucr.edu
*/

#include "../inc/Wall.h"

Wall :: Wall(bool iP){
  isPresent = iP;
}

Wall :: Wall(){
  isPresent = false;
}

void Wall :: markPresent(){
  isPresent = true;
}

void Wall :: markNotPresent(){
  isPresent = false;
}

bool Wall :: returnIsPresent(){
  return isPresent;
}
