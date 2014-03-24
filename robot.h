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

      int drawpath(float *arcx1,  float *arcy1,\
                    float *arcx2, float *arcy2,
                    int N);

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
      float r1,r2;     // inner and outer radius for arc path (mm)
      float th, dth;   // angle parameters used
      
};

#endif
