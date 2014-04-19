#include <time.h>
#include <sys/time.h>

float gettime(void) {

   static bool init = true;
   static struct timeval start, end;
   float dt;

   if (init) {
      gettimeofday(&start, NULL);
      gettimeofday(&end,   NULL);
      init = false;
   }

   // update the delta time dt

   gettimeofday(&end, NULL);
   dt = (float)((end.tv_sec*1000000 + end.tv_usec) -
        (start.tv_sec*1000000 + start.tv_usec))/1000000.0;
   gettimeofday(&start, NULL);

   return dt;
}
