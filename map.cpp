#include "map.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define MAP_SIZE 16384

#define MIN(A,B) A < B ? A : B
#define ABS(Z) Z < 0.0 ? -Z : Z

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
   float dist, mindist;
   bool initdone=false;

   // distance from circles

   for (i=0; i<Ncircles; i++) {
      dist = sqrtf((x - centerx[i])*(x - centerx[i]) + 
      (y - centery[i])*(y - centery[i]));
      dist -= radii[i];
      if (!initdone) {
         mindist = dist;
         initdone = true;
      } else {
         mindist = MIN(mindist, dist);
      }
   }

   /*
    * distance from lines
    * 
    *      |(y2-y1)*x0 - (x2-x1)*y0 - x1*y2 + x2*y1|
    *  d = -----------------------------------------
    *           sqrt((x2-x1)^2 + (y2-y1)^2)
    *
    *  line defined from the points (x1,y1) and (x2,y2) and the
    *  point is defined from (x0,y0)
    */
  
   for (i=0; i<Nlines; i++) {
      // insert check if point is within the line boundaries here
      dist = ABS((y2[i]-y1[i])*x - (x2[i]-x1[i])*y - x1[i]*y2[i] + x2[i]*y1[i])/
       sqrtf((x2[i]-x1[i])*(x2[i]-x1[i]) + (y2[i]-y1[i])*(y2[i]-y1[i]));
      if (!initdone) {
         mindist = dist;
         initdone = true;
      } else {
         mindist = MIN(mindist, dist);
      }
   }
std::cout << dist << std::endl;
   return mindist;
}
