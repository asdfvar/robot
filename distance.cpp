#include <math.h>
#include "map.h"
#include <iostream>

#define MAXDIST 10.0 // meters
#define MIN(A,B) (A) < (B) ? (A) : (B)

#define EPS 0.00001 // threshold to check if lines are parallel

class map;

float map::distance(float qx, float qy, float qdir) {

   float nqx, nqy, q2x, q2y;
   float pp12x, pp12y;
   float vlen, dotpr, t;
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

      pp12x /= vlen;
      pp12y /= vlen;

      dotpr = pp12x*nqx + pp12y*nqy;

      // return the max distance if look
      // direction is parallel to the line

      if (dotpr < EPS && false) dist = MAXDIST;

      // otherwise:

      else {

         t  = ( x1[i] + x2[i] ) * nqx + ( y1[i] + y2[i] ) * nqy;
         t -= 2.0 * ( qx*nqx + qy*nqy );
         t /= 2.0 * ( nqx*nqx + nqy*nqy );

         q2x = qx + t*nqx; q2y = qy + t*nqy;
         dotpr = (x2[i] - q2x) * (x1[i] - q2x) +
                 (y2[i] - q2y) * (y1[i] - q2y);

         // return the max distance if the line
         // is behind the look direction

         if (t < 0.0) dist = MAXDIST;

         // return the max distance if the intersection
         // of the line is not between the two points
         // that define the line

         else if (t >= 0.0 && dotpr > 0.0 && false) dist = MAXDIST;

         // return the distance to the line if it
         // actually hits the line between the two points

         else dist = sqrtf( (q2x - qx) * (q2x - qx) + (q2y - qy) * (q2y - qy) );
std::cout << qdir << " " << qx << " " << qy << " " << x1[i] << " " << x2[i] << " " << y1[i] << " " << y2[i] << std::endl;
      }

   mindist = MIN(mindist, dist);

   }

  /***********
   * Circles *
   ***********/

   for (i = 0; i < Ncircles; i++) {

      // stuff

   }

   return mindist;

}
