#include "robot.h"
#include "avoidance.h"
#include <stdio.h>

class robot;
class avoidance;

int robot::autonomous(void) {

  float v1[2], v2[2];
  avoidance avi;

  avi.eigenvectors(v1, v2, dist, angle, N_dist);

  printf("v1=%f,%f v2=%f,%f\n",v1[0],v1[1],v2[0],v2[1]);

  return 0;
}
