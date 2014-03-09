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

   private:

      float posx;   // Robot x-position
      float posy;   // Robot y-position
      float dir;    // Robot direction (radians)
      float speed;   // Robot speed
};

#endif
