#include "map.h"
#include <stdlib.h>
#include <stdio.h>

#define MAP_SIZE 16384

map::map(){
   mem = (float*) calloc(6*MAP_SIZE, sizeof(float));

   x1 = mem;
   y1 = x1 + MAP_SIZE;
   x2 = y1 + MAP_SIZE;
   y2 = x2 + MAP_SIZE;

   centers  = y2      + MAP_SIZE;
   radii    = centers +  MAP_SIZE;
}

map::~map(){
   delete mem;
   mem = NULL;
}

void map::hello(){
   printf("hello\n");
}
