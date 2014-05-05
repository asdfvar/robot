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
   N_dist = n_dist;
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
   N_dist = n_dist;
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

 /*
  * Populate the distance and directions array with the
  * robots local map data and return the number of points
  * that make up the distance and directions array
  *
  * if the distance and direction arrays are NULL, then
  * return the number of points that make up the distance
  * and directions array only
  */

int robot::getmap(float *distance, float *directions) {

   if (distance == 0 || directions == 0)
      return N_dist;
   
   for (int i = 0; i < N_dist; i++) {
      distance[i] = dist[i];
      directions[i] = angle[i];
   }

   return N_dist;
}

int robot::setposxy(float x, float y, float dr){
   posx = x;
   posy = y;
   dir  = dr;

   return 0;
}
