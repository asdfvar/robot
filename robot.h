#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "map.h"
class map;

#define MINOMEGA 0.01 // rad/s
#define MINSPEED 0.01 // m/s
#define n_dist 200

enum {FREE=0, CNTR, CNTRFIX, AUT};

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

      int setposxy(float x, float y, float dir);
      int setspeed(float spd);
      int setdir(float direction);

      int getlocalmap(map*);

      int drawpath(float relx, float rely, float reldir);
      int drawrobot(float relx, float rely, float reldir);
      int drawlocalmap(float relx, float rely, float reldir);
      int getmap(float *distances, float *directions);

      int move(unsigned char key);
      int unmove(unsigned char key);
      int collide(map *MAP);

   private:

      int mode;     // robot movement mode
      float mmove;  // robot movement parameters (special mode)
      float tturn;  // robot movement parameters (special mode)

      float posx;   // x-position
      float posy;   // y-position
      float dir;    // direction (radians)
      float speed;  // speed
      float omega;  // rotation rate (radians/second)

      float diameter; // robot diameter

      int N_dist;
      float dist[n_dist], angle[n_dist]; // local map details

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
