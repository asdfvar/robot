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

      float diameter; // robot diameter

     /*******************
      * visual arc path *
      *******************/

      float thetalen;  // length of projected visual path (radians)
      float radius;    // robot path radius
      bool  is_strait; // the case when the radius --> inf
      float th;   // angle parameters used
      
};

#endif
