#include "robot.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

#define SPEED 0.01
#define OMEGA 0.1

#define dSPEED 0.00002
#define dOMEGA 0.0002

float abs(float);

enum {DEF = 0, MOV};

static int mode = DEF;
static float mmove = 0.0;
static float tturn = 0.0;

int robot::update(float dt){

   if (mode == MOV){
      speed += mmove*dSPEED;
      omega += tturn*dOMEGA;
   }

   posx += speed*cosf(dir)*dt;
   posy += speed*sinf(dir)*dt;

   dir += omega*dt;

   if (omega > 0.001 || omega < -0.001){
      radius = abs(speed/omega);
      is_strait = false;
   } else
      is_strait = true;

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

float abs(float arg){
   return arg > 0.0 ? arg : -arg;
}
