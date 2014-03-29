#include "robot.h"
#include <math.h>
#include <stdlib.h>

#define SPEED 0.01
#define OMEGA 0.1

#define dSPEED 0.00002
#define dOMEGA 0.0002

enum {DEF = 0, MOV};

static int mode = DEF;
static float mmove = 0.0;
static float tturn = 0.0;

int robot::update(float dt){

#if 1
   if (mode == MOV){
      speed += mmove*dSPEED;
      omega += tturn*dOMEGA;
   }
#endif

   posx += speed*cosf(dir)*dt;
   posy += speed*sinf(dir)*dt;

   dir += omega*dt;

   return 0;
}

int robot::move(unsigned char key){

   switch (key){
      case 'w':
         if (mode == MOV)
            mmove = 1.0;
         else
            speed = SPEED;
         break;
      case 'a':
         if (mode == MOV)
            tturn = 1.0;
         else
            omega = OMEGA;
         break;
      case 'd':
         if (mode == MOV)
            tturn = -1.0;
         else
            omega = -OMEGA;
         break;
      case 's':
         if (mode == MOV)
            mmove = -1.0;
         else
            speed = -SPEED;
         break;
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
