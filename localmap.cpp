#include "map.h"

class map;

int map::localmap(float *dist, float angle[], int N, float xloc, float yloc, float dir) {

   int i;

   for (i = 0; i < N; i++) {

      dist[i] = distance(xloc, yloc, dir);

   }

   return 0;

}
