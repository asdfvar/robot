#include "robot.h"

robot::robot(float position_x, float position_y, float direction){
   posx  = position_x;
   posy  = position_y;
   dir   = direction;
   speed = 0.0f;
   omega = 0.0f;
}

robot::robot(){
   posx  = 0.0f;
   posy  = 0.0f;
   dir   = 0.0f;
   speed = 0.0f;
   omega = 0.0f;
}

robot::~robot(){}

float robot::getposx(void){
   return posx;
}

float robot::getposy(void){
   return posy;
}
