#include "map.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define MAP_SIZE 16384

#define MIN(A,B) A < B ? A : B

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

/*
 * get the distance from a point (x,y)
 */

float map::getdist(float x, float y) {

   int i;
   float dist, maxdist;
   bool initdone=false;

   // distance from circles

   for (i=0; i<Ncircles; i++) {
      dist = sqrtf((x - centerx[i])*(x - centerx[i]) + 
      (y - centery[i])*(y - centery[i]));
      dist -= radii[i];
      if (!initdone) {
         maxdist = dist;
         initdone = true;
      } else {
         maxdist = MIN(maxdist, dist);
      }
   }

   return maxdist;
}
