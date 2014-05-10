/*
 * the unit meters are somewhat redundant here. Any unit of displacement is acceptable as long as it
 * is consistent
 */

#include "robot.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "constants.h"

#define SPEED 1.0 // default 1 m/s
#define OMEGA 2.0 // default 1 rad/s

#define dSPEED 0.5   // increment in speed measured in m/s/s
#define dOMEGA 0.004 // increment in rotation rate measured in rad/s/s

#define ABS(A) (A > 0.0 ? A : -A)

enum {DEF = 0, MOV};

/*********************************
 * update the robot based on its
 * current parameters
 *********************************/

int robot::update(float dt){

   // update position in MOV mode while the key
   // is being pressed down

   if (mode == MOV){
      speed += mmove*(dSPEED*dt);
      omega += tturn*(4.0*dt);
      if (((omega > 0.0 && speed > 0.0) || (omega < 0.0 && speed < 0.0)) \
            && ABS(speed) >= MINSPEED && !is_strait)
         omega += mmove*(dSPEED*dt)/radius;
      if (((omega < 0.0 && speed > 0.0) || (omega > 0.0 && speed < 0.0)) \
            && ABS(speed) >= MINSPEED && !is_strait)
         omega -= mmove*(dSPEED*dt)/radius;
   }

   // update the radius and determine if the
   // robot is going straight or not

   if (omega > MINOMEGA || omega < -MINOMEGA){
      radius = ABS(speed/omega);
      is_strait = false;
   } else
      is_strait = true;

   // update the position and direction

   posx += speed*cosf(dir)*dt; // only first order accurate
   posy += speed*sinf(dir)*dt; // Exact is along the circular path

   dir += omega*dt;

   return 0;
}

/********
 * move *
 ********/

int robot::move(unsigned char key){

printf("mode=%d\n",mode);
   if (mode == DEF){
      switch (key){
         case 'w':
printf("forward\n");
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
      case 'A':
         speed = 0.0;
         omega = 0.0;
      case 'M':
         speed = 0.0;
         omega = 0.0;
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
