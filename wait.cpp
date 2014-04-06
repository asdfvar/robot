#include <ctime>

static bool init = false;
static clock_t end;

int wait(float dt){

   if (!init)
      initwait();

   while(clock() < end);

   end = clock() + dt*1000;

   return 0;
}

 /**************
  * initialize *
  **************/

int initwait(){

   end = 0;
   init = true

   return 0;
}
