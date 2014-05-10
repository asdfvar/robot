#ifndef _AVOIDANCE_H_
#define _AVOIDANCE_H_

#include "robot.h"
class robot;

class avoidance {

   public:

      avoidance();
      ~avoidance();

      int drawdirection(float v1[], float v2[],
                        float relx, float rely, float reldir,
                        float robx, float roby, float robdir);

      int eigenvectors(float *v1, float *v2, float *dist, float *angle, int N);
   private:

      float v1[2], v2[2]; // eigenvectors
      float robdir, robx, roby;


};

#endif
