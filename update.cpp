#include "robot.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include "constants.h"

#define SPEED 1.0 // default 1 m/s
#define OMEGA 2.0 // default 1 rad/s

#define dSPEED 0.002
#define dOMEGA 0.004

#define ABS(A) (A > 0.0 ? A : -A)

float abs(float);

enum {DEF = 0, MOV};

static int mode = DEF;
static float mmove = 0.0;
static float tturn = 0.0;
static bool init = true;
static struct timeval start, end;

int robot::update(){

   float dt;

   if (init){
      gettimeofday(&start, NULL);
      gettimeofday(&end, NULL);
      init = false;
   }

   // update position in MOV mode while the key
   // is being pressed down

   if (mode == MOV){
      speed += mmove*dSPEED;
      omega += tturn*dOMEGA;
      if (((omega > 0.0 && speed > 0.0) || (omega < 0.0 && speed < 0.0)) \
            && ABS(speed) >= MINSPEED && !is_strait)
         omega += mmove*dSPEED/radius;
      if (((omega < 0.0 && speed > 0.0) || (omega > 0.0 && speed < 0.0)) \
            && ABS(speed) >= MINSPEED && !is_strait)
         omega -= mmove*dSPEED/radius;
   }

   // update the radius and determine if the
   // robot is going straight or not

   if (omega > MINOMEGA || omega < -MINOMEGA){
      radius = abs(speed/omega);
      is_strait = false;
   } else
      is_strait = true;

   // update the delta time dt

   gettimeofday(&end, NULL);
   dt = (float)((end.tv_sec*1000000 + end.tv_usec) -
        (start.tv_sec*1000000 + start.tv_usec))/1000000.0;
   gettimeofday(&start, NULL);

   // update the position and direction

   posx += speed*cosf(dir)*dt * CONV;
   posy += speed*sinf(dir)*dt * CONV;

   dir += omega*dt;

   return 0;
}

/********
 * move *
 ********/

int robot::move(unsigned char key){

   if (mode == DEF){
      switch (key){
         case 'w':
            speed = SPEED;
            break;
         case 'a':
            omega = OMEGA;
            break;
         case 'd':
            omega = -OMEGA;
            break;
         case 's':
            speed = -SPEED;
            break;
         default:
            break;
      }
   } else if (mode == MOV){
      switch (key){
         case 'w':
            mmove = 1.0;
            break;
         case 'a':
            tturn = 1.0;
            break;
         case 'd':
            tturn = -1.0;
            break;
         case 's':
            mmove = -1.0;
            break;
      }
   }

   switch (key){
      case 'f':
         mode = MOV;
         break;
      case 'j':
         mode = DEF;
         speed = 0.0;
         omega = 0.0;
         break;
      default:
         break;
   }

   return 0;
}

/**********
 * unmove *
 **********/

int robot::unmove(unsigned char key){

   switch (key){
      case 'w':
         if (mode == MOV)
            mmove = 0.0;
         else if (mode == DEF)
            speed = 0.0;
         break;
      case 's':
         if (mode == MOV)
            mmove = 0.0;
         else if (mode == DEF)
            speed = 0.0;
         break;
      case 'a':
         if (mode == MOV)
            tturn = 0.0;
         else if (mode == DEF)
            omega = 0.0;
         break;
      case 'd':
         if (mode == MOV)
            tturn = 0.0;
         else if (mode == DEF)
            omega = 0.0;
         break;
      default:
         break;
   }

   return 0;
}

float abs(float arg){
   return arg > 0.0 ? arg : -arg;
}
