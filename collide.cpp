#include "robot.h"
#include "map.h"
#include <iostream>

int robot::collide(map *MAP){

   float dist;

   // get distance from robot to the nearest object
   dist = MAP->getdist(posx, posy);
   dist -= 0.5*diameter;

std::cout << dist << std::endl;

   return 0;
}
