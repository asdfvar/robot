/*
 * Draw the path of the robot
 */

#include "robot.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define ABS(A) (A > 0.0 ? A : -A)

int robot::drawpath(){

   int i,N = 20;
   float arcx1[20], arcy1[20];
   float arcx2[20], arcy2[20];
   float r1, r2;
   float tmp;
   float dirp = dir - 1.57079632679;
   float dth;
   float dp;
   float p;

   if (!is_strait){
      r1 = radius - diameter/2.0; r2 = radius + diameter/2.0;
      thetalen = 20*speed/radius;
      dth = (thetalen - 0.0)/((float)(N-1));
   } else {
      dp = speed;
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
         arcx1[i] = -diameter/2.0;
         arcx2[i] = diameter/2.0;
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
         for (i = 0, th = 3.14159; i < N; i++, th -= dth){
            arcx1[i] = r1*cosf(th);
            arcy1[i] = r1*sinf(th);
            arcx2[i] = r2*cosf(th);
            arcy2[i] = r2*sinf(th);
         }
      }
   }

#if 1
   // rotate the path to the robot direction
   for (i = 0; i < N; i++){
      tmp = arcx1[i]*cosf(dirp) - arcy1[i]*sinf(dirp);
      arcy1[i] = arcx1[i]*sinf(dirp) + arcy1[i]*cosf(dirp);
      arcx1[i] = tmp;
      tmp = arcx2[i]*cosf(dirp) - arcy2[i]*sinf(dirp);
      arcy2[i] = arcx2[i]*sinf(dirp) + arcy2[i]*cosf(dirp);
      arcx2[i] = tmp;
   }

   // translate to origin
   if (!is_strait){
      if ((omega > 0.0 && speed > 0.0) || (omega < 0.0 && speed < 0.0)){
         for (i = 0; i < N; i++){
            arcx1[i] -= radius*cosf(dirp);
            arcx2[i] -= radius*cosf(dirp);
            arcy1[i] -= radius*sinf(dirp);
            arcy2[i] -= radius*sinf(dirp);
         }
      } else if ((omega < 0.0 && speed > 0.0) || (omega > 0.0 && speed < 0.0)) {
         for (i = 0; i < N; i++){
            arcx1[i] += radius*cosf(dirp);
            arcx2[i] += radius*cosf(dirp);
            arcy1[i] += radius*sinf(dirp);
            arcy2[i] += radius*sinf(dirp);
         }
      }
   }

   // translate to position
   for (i = 0; i < N; i++){
      arcx1[i] += posx;
      arcx2[i] += posx;
      arcy1[i] += posy;
      arcy2[i] += posy;
   }
#endif

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

int robot::drawrobot(){

   int i;
   float x1,y1,x2,y2,x3,y3;
   float tmp;
   float x,y;
   const float sqrt3 = 1.7320508;

   x1 = -0.5*diameter*sqrt3/2.0;
   y1 = -0.5*diameter*0.6;
   x2 = 0.5*diameter*sqrt3/2.0;
   y2 = 0.0;
   x3 = -0.5*diameter*sqrt3/2.0;
   y3 = 0.5*diameter*0.6;

   tmp = x1*cosf(dir) - y1*sinf(dir);
   y1  = x1*sinf(dir) + y1*cosf(dir);
   x1  = tmp;
   tmp = x2*cosf(dir) - y2*sinf(dir);
   y2  = x2*sinf(dir) + y2*cosf(dir);
   x2  = tmp;
   tmp = x3*cosf(dir) - y3*sinf(dir);
   y3  = x3*sinf(dir) + y3*cosf(dir);
   x3  = tmp;

   x1 += posx;
   y1 += posy;
   x2 += posx;
   y2 += posy;
   x3 += posx;
   y3 += posy;

   // draw circle around robot
   glColor3ub(0, 255, 0);
   glBegin(GL_POLYGON);
   for (i = 0; i < 40; i++){
      x = posx + 0.05*cosf(2*3.1415926*(float)i/(float)40);
      y = posy + 0.05*sinf(2*3.1415926*(float)i/(float)40);
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
