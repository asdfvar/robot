#include "robot.h"

robot::robot(float position_x, float position_y, float direction){
   posx = position_x;
   posy = position_y;
   dir  = direction;
}

robot::robot(){
   posx = 0.0f;
   posy = 0.0f;
   dir  = 0.0f;
}

robot::~robot(){}
