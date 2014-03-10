#include "robot.h"
#include <math.h>

enum{SUC = 0, ERR = -1};

int robot::update(float dt){

   posy += speed*cosf(dir)*dt;
   posy += speed*sinf(dir)*dt;

   return SUC;
}
