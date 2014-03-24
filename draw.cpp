/*
 * Draw the path of the robot
 */

#include "robot.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define PI = 3.1415926;

int robot::drawpath(){

   int i,N = 20;
   float arcx1[20], arcy1[20];
   float arcx2[20], arcy2[20];
   float r1, r2;

   r = 0.5;
   r1 = r - 0.1; r2 = r + 0.1;
   thetalen = 2.0;
   dth = (thetalen - 0.0)/((float)(N-1));

   th = 0.0;
   for (i = 0; i < N; i++){
      arcx1[i] = r1*cosf(th);
      arcy1[i] = r1*sinf(th);
      th += dth;
   }
   th = 0.0;
   for (i = 0; i < N; i++){
      arcx2[i] = r2*cosf(th);
      arcy2[i] = r2*sinf(th);
      th += dth;
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

int robot::drawrobot(){

   int i;
   float x1,y1,x2,y2,x3,y3;
   float tmp;
   float x,y;

   x1 = -0.0433;
   y1 = -0.03;
   x2 = 0.0433;
   y2 = 0.0;
   x3 = -0.0433;
   y3 = 0.03;

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
