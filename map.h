#ifndef _MAP_H_
#define _MAP_H_

//#define MAP_SIZE 16384

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
      float distance(float qx, float qy, float qdir);

   private:

      float *x1, *y1, *x2, *y2;           // line parameters
      int Nlines;
      float *radii, *centerx, *centery;   // circle parameters
      int Ncircles;


};

#endif
