#include "avoidance.h"
#include "robot.h"
#include <cmath>

#define EPS 0.00001

class robot;

avoidance::avoidance() {}

int avoidance::action(robot *rob) {

   N_dist = rob->getmap(&dist[0], &angle[0]);

   return 0;

}

int avoidance::eigenvectors(float *v1, float *v2) {

   float lmbda1, lmbda2;
   float a11, a12, a21, a22;

   a11 = a12 = a21 = a22 = 0.0;

   float x[200], y[200];

  /*******************************
   * Populate the x and y arrays *
   *******************************/

   for (int k = 0; k < N_dist; k++) {
      x[k] = dist[k] * cosf(angle[k]);
      y[k] = dist[k] * sinf(angle[k]);
   }

  /**************************************************************
   * Perform the outer product to develop the covariance matrix *
   **************************************************************/

   for (int k = 0; k < N_dist; k++) {
      a11 += x[k] * x[k];
      a12 += x[k] * y[k];
      a22 += y[k] * y[k];
   }
   a21 = a12;

  /*****************************
   * Calculate the eigenvalues *
   *****************************/

   float b, D;

   b = a11 + a22;
   D = b*b - 4 * ( a11*a22 - a12*a21 );
   b *= 0.5;
   D = 0.5 * sqrtf(D);

   lmbda1 = b + D;
   lmbda2 = b - D;

  /******************************
   * Calculate the eigenvectors *
   ******************************/

   float len;

   if (a21 > EPS) {
      v1[1] = 1.0;
      v1[0] = (lmbda1 - a22) / a21;
      v2[1] = 1.0;
      v2[0] = (lmbda2 - a22) / a21;
   } else if (a12 > EPS) {
      v1[0] = 1.0;
      v1[1] = (lmbda1 - a11) / a12;
      v2[0] = 1.0;
      v2[1] = (lmbda2 - a11) / a12;
   } else {
      v1[0] = 1.0;
      v1[1] = 0.0;
      v2[0] = 0.0;
      v2[1] = 1.0;
   }

   len = sqrtf(v1[0] * v1[0] + v1[1] * v1[1]);

   v1[0] /= len;
   v1[1] /= len;

   return 0;
}
