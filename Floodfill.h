#ifndef FLOODFILL_H
#define FLOODFILL_H
#define NORTH      1
#define EAST       2
#define SOUTH      4
#define WEST       8
#define VISITED      16
#define ONROUTE      32

#define NOTNORTH  (255-NORTH)
#define NOTEAST   (255-EAST)
#define NOTSOUTH  (255-SOUTH)
#define NOTWEST   (255-WEST)
#define ALLWALLS  (NORTH|EAST|SOUTH|WEST)

// maze storage
#define NUMCELLS 256
extern CELL maze[NUMCELLS] ;
extern CELL map[NUMCELLS];

/*
  floodMaze solves the maze using wall data found in the array maze
  and places the flooding data - effectively the routemap - into
  the array map. The destination cell is passed in to the function
  to allow solving for any location.
  The state of map on entry is not important and it is not important
  whether all the walls have been found. The algorithm simply performs
  the flood based on what it knows at the time it is called.
  At worst, up to 255 passes are made through the maze date in generating
  the map. If that many passes are made, there has been an error and
  the maze should be considered to be seriously in error.
  Passes of the algorithm are made until either the limit has been reached
  or the change flag indicates that none of the map data has changed in
  that pass. At that point the maze can be considered to have been solved.
  Clearly, unless all the walls have been observed, the map will contain
  invalid paths. The mouse will discover new walls and call the solver again
  as needed.
  The function returns the number of passes required to solve the maze.
  A returned value of 255 indicates an error.
  Note that the array is allowed to wrap around in a most dangerous
  manner by relying on the 8 bit pointer.
  This should not be a real problem in as much as the existence of the outer
  walls means we never have to make use of the value
*/

byte floodMaze(byte goal)
{
  byte i,j;
  byte now,next;
  byte passes;
  byte cellwalls;    // the wall data for a given cell
  byte changed;

  i = 0;
  do{
    map[i--] = 255;
  } while (i);

  map[goal]=0;
  passes = 0;
  now = 0;
  next = now+1;
  do {
    changed = 0;
    i = 0;
    do {
      if (map==now) {
        cellwalls=maze;
        if ((cellwalls & NORTH) == 0) {
          j = i+1;
          if (map[j] == 255){ map[j] = next; changed=1;}
        }
        if ((cellwalls & EAST) == 0) {
          j = i + 16;
          if (map[j] == 255){ map[j] = next; changed=1;}
        }
        if ((cellwalls & SOUTH) == 0) {
          j = i + 255;
          if (map[j] == 255){ map[j] = next; changed=1;}
        }
        if ((cellwalls & WEST) == 0) {
          j = i + 240;
          if (map[j] == 255){ map[j] = next; changed=1;}
        }
      }
      i--;
    } while(i);
    now  = now+1;
    next = now+1;
    passes++;
  } while(changed);
  return passes;
}

#endif /*FLOODFILL_H*/
