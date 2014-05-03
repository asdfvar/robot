#ifndef _MAP_H_
#define _MAP_H_

#include "robot.h"
class robot;

class map{
   public:

      /****************
       * Constructors *
       ****************/

      map();
      ~map();

      int loadlines(float *X1, float *Y1, float *X2, float *Y2, int N);
      int loadcircles(float *CX, float *CY, float *R, int N);
      int draw(float relx, float rely, float reldir);

      float getdist(float x, float y);
      int localmap(float *dist, float angle[], int N, float xloc, float yloc, float dir);

   private:

      float *mem;
      float *x1, *y1, *x2, *y2;                 // line parameters
      int Nlines;
      float *tmp, *radii, *centerx, *centery;   // circle parameters
      int Ncircles;

      float distance(float qx, float qy, float qdir);

};

#endif
