#ifndef _ROBOT_H_
#define _ROBOT_H_

class robot{
   public:
      float posx;   // x-position
      float posy;   // y-position

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

   private:

      float dir;    // direction (radians)
      float speed;  // speed
      float omega;  // rotation rate (radians/second)
};

#endif
