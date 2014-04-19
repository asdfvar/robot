#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "map.h"
class map;

#define MINOMEGA 0.01 // rad/s
#define MINSPEED 0.01 // m/s

class robot{
   public:

     /****************
      * Constructors *
      ****************/

      robot(float posx, float posy, float dir);
      robot();
      ~robot();

     /*************
      * Functions *
      *************/

      int update(float dt);

      float getposx();
      float getposy();
      float getdir();

      int setposxy(float x, float y);

      int drawpath(int mode);
      int drawrobot(int mode);

      int move(unsigned char key);
      int unmove(unsigned char key);
      int collide(map *MAP);

   private:
   
      float posx;   // x-position
      float posy;   // y-position
      float dir;    // direction (radians)
      float speed;  // speed
      float omega;  // rotation rate (radians/second)

      float diameter; // robot diameter

     /*******************
      * visual arc path *
      *******************/

      float thetalen;  // length of projected visual path (radians)
      float radius;    // robot path radius
      bool  is_strait; // the case when the radius --> inf
      float th;   // angle parameters used

      /*********/

      bool collision;   // collision
      
};

#endif
