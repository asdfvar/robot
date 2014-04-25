#include "robot.h"

robot::robot(float position_x, float position_y, float direction){
   posx  = position_x;
   posy  = position_y;
   dir   = direction;
   diameter = 0.1;
   speed = 0.0f;
   omega = 0.0f;
   is_strait = true;
   collision = false;
   mode = 0;
   mmove = 0.0;
   tturn = 0.0;
}

robot::robot(){
   posx  = 0.0f;
   posy  = 0.0f;
   dir   = 0.0f;
   diameter = 0.1;
   speed = 0.0f;
   omega = 0.0f;
   is_strait = true;
   collision = false;
   mode = 0;
   mmove = 0.0;
   tturn = 0.0;
}

robot::~robot(){}

float robot::getposx(void){
   return posx;
}

float robot::getposy(void){
   return posy;
}

float robot::getdir(void){
   return dir;
}

int robot::setposxy(float x, float y){
   posx = x;
   posy = y;

   return 0;
}
