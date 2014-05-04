#include <math.h>
#include "map.h"
#include <iostream>

#define MAXDIST 10.0 // meters
#define MIN(A,B) (A) < (B) ? (A) : (B)

#define EPS 0.00001 // threshold to check if lines are parallel

class map;

float map::distance(float qx, float qy, float qdir) {

   float nqx, nqy;
   float pp12x, pp12y;
   float qp1x, qp1y, qp2x, qp2y;
   float npx, npy;
   float vlen, dotpr;
   float dist, mindist = MAXDIST;
   int i;

   nqx = cosf(qdir); nqy = sinf(qdir);

  /*********
   * Lines *
   *********/

   for (i = 0; i < Nlines; i++) {

      pp12x = x2[i] - x1[i];
      pp12y = y2[i] - y1[i];

      vlen = sqrtf(pp12x*pp12x + pp12y*pp12y);

      npx = pp12x/vlen;
      npy = pp12y/vlen;

      dotpr = npx*nqx + npy*nqy;

      qp1x = x1[i] - qx; qp1y = y1[i] - qy;
      qp2x = x2[i] - qx; qp2y = y2[i] - qy;

      // return the max distance if look
      // direction is parallel to the line

      if (dotpr > 1.0 - EPS && false) { dist = MAXDIST; }

      // otherwise:

      else {

         dist  = npy * (x1[i] - qx) - npx * (y1[i] - qy);
         dist /= nqx * npy - nqy * npx;
         
         // return the max distance if the line
         // is behind the look direction

         if (dist < 0.0) { dist = MAXDIST; }

         // return the max distance if the intersection
         // of the line is not between the two points
         // that define the line

         else if ((nqx*qp1y - nqy*qp1x)*(nqx*qp2y - nqy*qp2x) > 0.0){ dist = MAXDIST; }

         // actually hits the line between the two points

      }

   mindist = MIN(mindist, dist);

   }

  /***********
   * Circles *
   ***********/

   float px, py;
   float ndp, D;

   for (i = 0; i < Ncircles; i++) {

      px = centerx[i] - qx;
      py = centery[i] - qy;

      ndp = nqx*px + nqy*py;

      D = ndp*ndp + radii[i]*radii[i] - (px*px + py*py);

      if (D < 0.0) { dist = MAXDIST; }

      else { dist = ndp - sqrtf(D); }

      if (dist < 0.0) { dist = MAXDIST; }

      mindist = MIN(mindist, dist);

   }

   return mindist;

}
