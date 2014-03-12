#include "map.h"
#include <stdlib.h>
#include <stdio.h>

#define MAP_SIZE 16777216

map::map(){
   x = (float*) calloc(MAP_SIZE, sizeof(float));
   y = (float*) calloc(MAP_SIZE, sizeof(float));
}

map::~map(){
   delete x;
   x = NULL;

   delete y;
   y = NULL;
}

void map::hello(){
   printf("hello\n");
}
