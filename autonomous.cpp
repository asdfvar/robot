#include "robot.h"
#include "avoidance.h"
#include <stdio.h>
#include <cmath>

class robot;
class avoidance;

int robot::autonomous(void) {

  avoidance avi;

  // find the vector that maximizes the variance of
  // the local map

  avi.eigenvectors(v1, v2, dist, angle, N_dist);

  // fix the direction 0 <= dir <= pi

  if (v1[0] < 0.0 ) {
     v1[0] = -v1[0];
     v1[1] = -v1[1];
  } else {
     v1[0] = v1[0];
     v1[1] = v1[1];
  }

  speed = rho;
  omega = alpha*atan2f(v1[1], v1[0]);

  return 0;
}

int robot::drawautonomous(float relx, float rely, float reldir) {

  avoidance avi;

  avi.drawdirection(v1, v2,
                    relx, rely, reldir,
                    posx, posy, dir);

  return 0;
}
