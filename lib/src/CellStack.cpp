/*
Andrew Nava-JuarezCa
anava014@ucr.edu
*/

#include "../inc/CellStack.h"

CellStack :: CellStack(){
  top = -1;
}

void CellStack :: push(Cell c){
  if(top >= 512){
    while(1) {tone(23, 500);}
  }

  stack[++top] = c;
}

Cell CellStack :: pop(){
  if(top == -1){
    while(1) {}
  }

  Cell temp = stack[top--];
  return temp;

}

bool CellStack :: isEmpty(){
  return (top == -1);
}

Cell CellStack :: peek(){
  if(top == -1){
    while(1) {tone(23, 500);}
  }

  return stack[top];
}
