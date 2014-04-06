#include "map.h"

/**************
 * load lines *
 **************/

int map::loadlines(float *X1, float *Y1, float *X2, float *Y2, int N){

   int i;
   float *x1p, *y1p, *x2p, *y2p;

   x1p = x1 + Nlines;
   y1p = y1 + Nlines;
   x2p = x2 + Nlines;
   y2p = y2 + Nlines;

   for (i = 0; i < N; i++){
      x1p[i] = X1[i];
      y1p[i] = Y1[i];
      x2p[i] = X2[i];
      y2p[i] = Y2[i];
   }

   Nlines += N;
   
   return 0;
}

/****************
 * load circles *
 ****************/

int map::loadcircles(float *CX, float *CY, float *R, int N){

   int i;
   float *cpx, *cpy, *rp;

   cpx = centerx + Ncircles;
   cpy = centery + Ncircles;
   rp  = radii   + Ncircles;

   for (i = 0; i < N; i++){
      cpx[i] = CX[i];
      cpy[i] = CY[i];
      rp[i] = R[i];
   }

   Ncircles += N;

   return 0;
}
