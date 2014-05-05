#ifndef _AVOIDANCE_H_
#define _AVOIDANCE_H_

#include "robot.h"
class robot;

class avoidance {

   public:

      avoidance();
      ~avoidance();

      int action(robot*);

   private:

      int N_dist;
      float dist[200], angle[200]; // the distance and angle arrays of the robot

      int eigenvectors(float *v1, float *v2);

};

#endif
