#ifndef _AVOIDANCE_H_
#define _AVOIDANCE_H_

#include "robot.h"
class robot;

class avoidance {

   public:

      avoidance();
      ~avoidance();

      int load(robot*);
      int drawdirection(float relx, float rely, float reldir);

      int eigenvectors(float *v1, float *v2, float *dist, float *angle, int N);
   private:

      float v1[2], v2[2]; // eigenvectors
      float robdir, robx, roby;

#if 0
      int N_dist;
      float dist[200], angle[200]; // the distance and angle arrays of the robot
#endif


};

#endif
