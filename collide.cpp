#include "robot.h"
#include "map.h"
#include <iostream>

int robot::collide(map *MAP){

   float dist;

   dist = MAP->getdist(posx, posy);

std::cout << dist << std::endl;

   return 0;
}
