#include "robot.h"
#include <math.h>

int robot::update(float dt){

   posx += speed*cosf(dir)*dt;
   posy += speed*sinf(dir)*dt;

   dir += omega*dt;

   return 0;
}
