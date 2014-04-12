#ifndef _MAP_H_
#define _MAP_H_

#include "robot.h"

class map{
   public:

      /****************
       * Constructors *
       ****************/

      map();
      ~map();

      int loadlines(float *X1, float *Y1, float *X2, float *Y2, int N);
      int loadcircles(float *CX, float *CY, float *R, int N);
      int draw(robot rob, int mode);

   private:

      float *mem;
      float *x1, *y1, *x2, *y2;                 // line parameters
      int Nlines;
      float *tmp, *radii, *centerx, *centery;   // circle parameters
      int Ncircles;

};

#endif
