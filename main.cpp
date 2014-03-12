#include <stdio.h>
#include "robot.h"
#include "map.h"

int main(){

   map *MAP = new map();
   robot rob;
   

int i;
for (i=0; i < 13; i++){
   rob.update(0.1);
   printf("robot position = %f, %f\n", rob.getposx(), rob.getposy());
}

   MAP->hello();

   delete MAP;
   return 0;
}
