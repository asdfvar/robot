#include "map.h"
#include <stdlib.h>
#include <iostream>

#define MAP_SIZE 16384

map::map(){

   int memsize = 7*MAP_SIZE;

   if ((mem = (float*) calloc(memsize, sizeof(float))) == NULL)
      std::cout << "Error allocating memory for the map" << std::endl;

   std::cout << (memsize*sizeof(float))/1024 << 
      " MB allocated for mapping" << std::endl;

   x1 = mem;
   y1 = x1 + MAP_SIZE;
   x2 = y1 + MAP_SIZE;
   y2 = x2 + MAP_SIZE;

   centerx  = y2      + MAP_SIZE;
   centery  = centerx + MAP_SIZE;
   radii    = centery + MAP_SIZE;

   Nlines = Ncircles = 0;
}

map::~map(){
   delete mem;
   std::cout << "map memory freed" << std::endl;
   mem = NULL;
}

