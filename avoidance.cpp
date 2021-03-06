#include "avoidance.h"
#include "robot.h"
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "constants.h"

#define EPS 0.00001

class robot;

avoidance::avoidance(void) {}

///////////////////////////

avoidance::~avoidance(void) {}

//////////////////////////////////////

/*
 * eigenvectors from a 2x2 matrix
 */

int avoidance::eigenvectors(float *v1, float *v2, float *dist, float *angle, int N_dist) {

   float lmbda1, lmbda2;
   float a11, a12, a21, a22;

   a11 = a12 = a21 = a22 = 0.0;

   float x[240], y[240];

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

   if (a21 > EPS || a21 < -EPS) {
      v1[1] = 1.0;
      v1[0] = (lmbda1 - a22) / a21;
      v2[1] = 1.0;
      v2[0] = (lmbda2 - a22) / a21;
   } else if (a12 > EPS || a12 < -EPS) {
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

   len = sqrtf(v2[0] * v2[0] + v2[1] * v2[1]);

   v2[0] /= len;
   v2[1] /= len;

   float tmp;

   if (lmbda2 > lmbda1) {
      tmp = v1[0];
      v1[0] = v2[0];
      v2[0] = tmp;

      tmp = v1[1];
      v1[1] = v2[1];
      v2[1] = tmp;
   }

   return 0;
}

int avoidance::drawdirection(float v1[], float v2[],
                             float relx, float rely, float reldir,
                             float robx, float roby, float robdir) {

  extern float CONV;

  glLineWidth(2.5);
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);

  // draw the base of the arrow

  float xpos, ypos;

  xpos = robx - relx;
  ypos = roby - rely;
  glVertex3f(xpos*CONV, ypos*CONV, 0.0);

  // define the pointing direction

  float pointdir;

  pointdir = reldir - robdir;

  float cospointdir = cosf(pointdir);
  float sinpointdir = sinf(pointdir);

  // rotate the pointing direction to the maps perspective

  xpos += 0.2*( v1[0]*cospointdir + v1[1]*sinpointdir);
  ypos += 0.2*(-v1[0]*sinpointdir + v1[1]*cospointdir);

  // transform to the visual window

  glVertex3f(xpos*CONV, ypos*CONV, 0.0);

  glEnd();

  return 0;
}
