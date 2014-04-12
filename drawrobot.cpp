/*
 * Draw the path of the robot
 */

#include "robot.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "constants.h"

#define PI 3.1415926535
#define ABS(A) (A > 0.0 ? A : -A)

/*******************
 * draw robot path *
 *******************/

int robot::drawpath(int mode){

   int i,N = 40;
   float arcx1[40], arcy1[40];
   float arcx2[40], arcy2[40];
   float r1, r2;
   float tmp;
   float dirp = dir - PI/2.0;
   float dth;
   float dp;
   float p;

   if (!is_strait){
      r1 = radius - diameter/2.0; r2 = radius + diameter/2.0;
      r1 *= CONV; r2 *= CONV;
      thetalen = speed/radius;
      dth = (thetalen - 0.0)/((float)(N-1));
   } else {
      dp = speed/(float)N * CONV;
   }

  /*****************************
   * draw the arch of the path *
   *****************************/

   // if the robot is not moving, exit

   if (speed < MINSPEED && speed > -MINSPEED)
      return -1;

   // get the arc

   if (is_strait){
      for (i = 0, p = 0.0; i < N; p += dp, i++){
         arcx1[i] = -diameter/2.0 * CONV;
         arcx2[i] = diameter/2.0 * CONV;
         arcy1[i] = p;
         arcy2[i] = p;
      }
   } else {
      if ((omega > 0.0 && speed > 0.0) || (omega < 0.0 && speed < 0.0)){
         for (i = 0, th = 0.0; i < N; i++, th += dth){
            arcx1[i] = r1*cosf(th);
            arcy1[i] = r1*sinf(th);
            arcx2[i] = r2*cosf(th);
            arcy2[i] = r2*sinf(th);
         }
      } else if ((omega < 0.0 && speed > 0.0) || (omega > 0.0 && speed < 0.0)) {
         for (i = 0, th = PI; i < N; i++, th -= dth){
            arcx1[i] = r1*cosf(th);
            arcy1[i] = r1*sinf(th);
            arcx2[i] = r2*cosf(th);
            arcy2[i] = r2*sinf(th);
         }
      }
   }

   // rotate the path to the robot direction

   if (mode != 2){
   for (i = 0; i < N; i++){
      tmp = arcx1[i]*cosf(dirp) - arcy1[i]*sinf(dirp);
      arcy1[i] = arcx1[i]*sinf(dirp) + arcy1[i]*cosf(dirp);
      arcx1[i] = tmp;
      tmp = arcx2[i]*cosf(dirp) - arcy2[i]*sinf(dirp);
      arcy2[i] = arcx2[i]*sinf(dirp) + arcy2[i]*cosf(dirp);
      arcx2[i] = tmp;
   }
   }

   // translate to origin

   if (mode == 2){
      if ((omega > 0.0 && speed > 0.0) || (omega < 0.0 && speed < 0.0)){
         for (i = 0; i < N; i++){
            arcx1[i] -= radius*CONV;
            arcx2[i] -= radius*CONV;
         }
      } else if ((omega < 0.0 && speed > 0.0) || (omega > 0.0 && speed < 0.0)) {
         for (i = 0; i < N; i++){
            arcx1[i] += radius*CONV;
            arcx2[i] += radius*CONV;
         }
      }
   } else {
   if (!is_strait){
      if ((omega > 0.0 && speed > 0.0) || (omega < 0.0 && speed < 0.0)){
         for (i = 0; i < N; i++){
            arcx1[i] -= radius*cosf(dirp)*CONV;
            arcx2[i] -= radius*cosf(dirp)*CONV;
            arcy1[i] -= radius*sinf(dirp)*CONV;
            arcy2[i] -= radius*sinf(dirp)*CONV;
         }
      } else if ((omega < 0.0 && speed > 0.0) || (omega > 0.0 && speed < 0.0)) {
         for (i = 0; i < N; i++){
            arcx1[i] += radius*cosf(dirp)*CONV;
            arcx2[i] += radius*cosf(dirp)*CONV;
            arcy1[i] += radius*sinf(dirp)*CONV;
            arcy2[i] += radius*sinf(dirp)*CONV;
         }
      }
   }
   }

   // translate to position

   if (mode == 0)
      for (i = 0; i < N; i++){
         arcx1[i] += posx;
         arcx2[i] += posx;
         arcy1[i] += posy;
         arcy2[i] += posy;
      }

   glColor3ub(255, 255, 255);
   for (i = 0; i < N-1; i++){
      glBegin(GL_POLYGON);
      glVertex3f(arcx1[i], arcy1[i], 0.0);
      glVertex3f(arcx1[i+1], arcy1[i+1], 0.0);
      glVertex3f(arcx2[i+1], arcy2[i+1], 0.0);
      glVertex3f(arcx2[i], arcy2[i], 0.0);
      glEnd();
   }

return 0;
}

/**************
 * draw robot *
 **************/

int robot::drawrobot(int mode){

   int i;
   float x1,y1,x2,y2,x3,y3;
   float tmp;
   float x,y;
   const float sqrt3 = 1.7320508;

   x1 = -diameter/2.0*sqrt3/2.0 * CONV;
   y1 = -diameter/2.0*0.6 * CONV;
   x2 = diameter/2.0*sqrt3/2.0 * CONV;
   y2 = 0.0 * CONV;
   x3 = -diameter/2.0*sqrt3/2.0 * CONV;
   y3 = diameter/2.0*0.6 * CONV;

   // rotate robot to its direction

   if (mode == 2) {
      tmp = x1; x1 = y1; y1 = tmp;
      tmp = x2; x2 = y2; y2 = tmp;
      tmp = x3; x3 = y3; y3 = tmp;
   } else {
      tmp = x1*cosf(dir) - y1*sinf(dir);
      y1  = x1*sinf(dir) + y1*cosf(dir);
      x1  = tmp;
      tmp = x2*cosf(dir) - y2*sinf(dir);
      y2  = x2*sinf(dir) + y2*cosf(dir);
      x2  = tmp;
      tmp = x3*cosf(dir) - y3*sinf(dir);
      y3  = x3*sinf(dir) + y3*cosf(dir);
      x3  = tmp;
   }

   if (mode == 0){
      x1 += posx;
      y1 += posy;
      x2 += posx;
      y2 += posy;
      x3 += posx;
      y3 += posy;
   }

   // draw circle around robot

   glColor3ub(0, 255, 0);
   glBegin(GL_POLYGON);
   for (i = 0; i < 40; i++){
      if (mode == 0){
         x = posx + diameter/2.0*cosf(2*PI*(float)i/(float)40) * CONV;
         y = posy + diameter/2.0*sinf(2*PI*(float)i/(float)40) * CONV;
      } else if (mode == 1 || mode == 2){
         x = diameter/2.0*cosf(2*PI*(float)i/(float)40) * CONV;
         y = diameter/2.0*sinf(2*PI*(float)i/(float)40) * CONV;
      }
      glVertex3f(x, y, 0.0);
   }
   glEnd();

   // draw robot

   glColor3ub(255, 0, 0);
   glBegin(GL_POLYGON);
      glVertex3f(x1, y1, 0.0);
      glVertex3f(x2, y2, 0.0);
      glVertex3f(x3, y3, 0.0);
   glEnd();


return 0;
}
