#include "robot.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

#define SPEED 0.01
#define OMEGA 0.1

#define dSPEED 0.00002
#define dOMEGA 0.0002

#define ABS(A) (A > 0.0 ? A : -A)

float abs(float);

enum {DEF = 0, MOV};

static int mode = DEF;
static float mmove = 0.0;
static float tturn = 0.0;

int robot::update(float dt){

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

   posx += speed*cosf(dir)*dt;
   posy += speed*sinf(dir)*dt;

   dir += omega*dt;

   if (omega > MINOMEGA || omega < -MINOMEGA){
      radius = abs(speed/omega);
      is_strait = false;
   } else
      is_strait = true;

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
      case 'q':
         exit(1);
         break;
      default:
         break;
   }

   return 0;
}

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
