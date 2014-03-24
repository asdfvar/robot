#include "robot.h"
#include <math.h>
#include <stdlib.h>

int robot::update(float dt){

   posx += speed*cosf(dir)*dt;
   posy += speed*sinf(dir)*dt;

   dir += omega*dt;

   return 0;
}

int robot::move(unsigned char key){

   switch (key){
      case 'w':
         speed = 0.01;
         break;
      case 'a':
         omega = 0.1;
         break;
      case 'd':
         omega = -0.1;
         break;
      case 's':
         speed = -0.01;
         break;
      case 'q':
         exit(1);
         break;
      default:
         break;
   }

   return 0;
}

int robot::unmove(unsigned char key){

   switch (key){
      case 'w':
         speed = 0.0;
         break;
      case 's':
         speed = 0.0;
         break;
      case 'a':
         omega = 0.0;
         break;
      case 'd':
         omega = 0.0;
         break;
      default:
         break;
   }

   return 0;
}
