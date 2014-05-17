#include "map.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define MAP_SIZE 16384

#define MIN(A,B) A < B ? A : B
#define ABS(Z) Z < 0.0 ? -Z : Z

static float *mem;

map::map(){

   mem = new float[7*MAP_SIZE];

   std::cout << (7*MAP_SIZE*sizeof(float))/1024 << 
      " MB allocated for mapping" << std::endl;

   float *Line_mem, *Circ_mem;

   Line_mem = mem;
   Circ_mem = mem + 4*MAP_SIZE;

   x1 = Line_mem;
   y1 = x1 + MAP_SIZE;
   x2 = y1 + MAP_SIZE;
   y2 = x2 + MAP_SIZE;

   centerx  = Circ_mem + MAP_SIZE;
   centery  = centerx  + MAP_SIZE;
   radii    = centery  + MAP_SIZE;

   Nlines = Ncircles = 0;
}

map::~map(){
   delete mem;
   std::cout << "map memory freed" << std::endl;
   mem = NULL;
}

/*
 * get the distance from a point (x,y)
 * to the nearest object on the map
 */

float map::getdist(float x, float y) {

   int i;
   float dist, mindist = 0.0;
   float Dp1, Dp2, Dp1p2;
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

      // get distance to the line. The line is a finite distance
      // so some consideration must be set.

      Dp1p2 = (x2[i]-x1[i])*(x2[i]-x1[i]) + (y2[i]-y1[i])*(y2[i]-y1[i]);
      Dp1   = (x-x1[i])*(x-x1[i]) + (y-y1[i])*(y-y1[i]);
      Dp2   = (x-x2[i])*(x-x2[i]) + (y-y2[i])*(y-y2[i]);

      if ( Dp1 + Dp1p2 < Dp2 )
         dist = sqrtf(Dp1);
      else if ( Dp2 + Dp1p2 < Dp1)
         dist = sqrtf(Dp2);
      else {
         dist = (y2[i]-y1[i])*x - (x2[i]-x1[i])*y - x1[i]*y2[i] + x2[i]*y1[i];
         dist = ABS(dist);
         dist /= sqrtf(Dp1p2);
      }

      if (!initdone) {
         mindist = dist;
         initdone = true;
      } else {
         mindist = MIN(mindist, dist);
      }
   }

   return mindist;
}
