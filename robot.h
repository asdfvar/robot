#ifndef _ROBOT_H_
#define _ROBOT_H_

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

      int drawpath();
      int drawrobot();

      int move(unsigned char key);
      int unmove(unsigned char key);

   private:
   
      float posx;   // x-position
      float posy;   // y-position
      float dir;    // direction (radians)
      float speed;  // speed
      float omega;  // rotation rate (radians/second)

     /*******************
      * visual arc path *
      *******************/

      float thetalen;  // length of projected visual path (radians)
      float r;         // robot path radius
      float th, dth;   // angle parameters used
      
};

#endif
