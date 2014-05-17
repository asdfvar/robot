#include <time.h>
#include <sys/time.h>
#include <iostream>

#define SEC 2.0

float gettime(void) {

   static bool init = true;
   static struct timeval start, end;
   static float sumtime = 0.0;
   static int Nsum = 0;
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

   sumtime += dt;
   Nsum++;

   if (sumtime >= SEC) {

      std::cout << "average processing time = "
           << sumtime / (float) Nsum
           << " <=> "
           << (float) Nsum / sumtime
           << " fps"
           << std::endl;

      sumtime = 0.0;
      Nsum = 0;

   }

   gettimeofday(&start, NULL);

   return dt;
}
