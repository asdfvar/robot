/*
 * draw the map with respect to the shift from the origin x0, y0
 *
 */

#include "map.h"
#include "robot.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include "constants.h"

#define CIRCRES 80
#define PI 3.1415926

int map::draw(robot rob, int mode){

   int i,k;
   float x,y,x0,y0,dir,tmp;

   x0 = rob.getposx();
   y0 = rob.getposy();
   dir = rob.getdir() - PI/2.0;
   /**************
    * draw lines *
    **************/

   for (i = 0; i < Nlines; i++){
      glLineWidth(2.5); 
      glColor3f(1.0, 1.0, 0.0);
      glBegin(GL_LINES);
        x = x1[i];
        y = y1[i];
        if (mode == 1 || mode == 2) {
           x -= x0;
           y -= y0;
        }
        if (mode == 2) {
           tmp = x*cosf(dir) + y*sinf(dir);
           y   = -x*sinf(dir) + y*cosf(dir);
           x = tmp;
        }
        glVertex3f(x, y, 0.0);
        x = x2[i];
        y = y2[i];
        if (mode == 1 || mode == 2) {
           x -= x0;
           y -= y0;
        }
        if (mode == 2) {
           tmp = x*cosf(dir) + y*sinf(dir);
           y   = -x*sinf(dir) + y*cosf(dir);
           x = tmp;
        }
        glVertex3f(x, y, 0.0);
      glEnd();
   }

   /****************
    * draw circles *
    ****************/

   for (i = 0; i < Ncircles; i++){
      glBegin(GL_POLYGON);
      for (k = 0; k < CIRCRES; k++){
         x = (centerx[i] + radii[i]*cosf(2*PI*(float)k/(float)CIRCRES))*CONV;
         y = (centery[i] + radii[i]*sinf(2*PI*(float)k/(float)CIRCRES))*CONV;
         if (mode == 1 || mode == 2) {
            x -= x0;
            y -= y0;
         }
         if (mode == 2) {
            tmp = x*cosf(dir) + y*sinf(dir);
            y   = -x*sinf(dir) + y*cosf(dir);
            x = tmp;
         }
         glVertex3f(x, y, 0.0);
      }
      glEnd();
   }

   return 0;
}
