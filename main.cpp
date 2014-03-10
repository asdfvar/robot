#include "robot.h"
#include <stdio.h>

int main(){

   robot rob;

int i;
for (i=0; i < 40; i++){
   rob.update(0.1);
   printf("robot position = %f, %f\n", rob.getposx(), rob.getposy());
}


   return 0;
}
