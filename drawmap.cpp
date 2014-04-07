#include "map.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include "constants.h"

#define CIRCRES 80
#define PI 3.1415926

int map::draw(){

   int i;

   /**************
    * draw lines *
    **************/

   for (i = 0; i < Nlines; i++){
      glLineWidth(2.5); 
      glColor3f(1.0, 1.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(x1[i], y1[i], 0.0);
      glVertex3f(x2[i], y2[i], 0);
      glEnd();
   }

   /****************
    * draw circles *
    ****************/

   int k;
   float x,y;

   for (i = 0; i < Ncircles; i++){
      glBegin(GL_POLYGON);
      for (k = 0; k < CIRCRES; k++){
         x = centerx[i] + radii[i]*cosf(2*PI*(float)k/(float)CIRCRES);
         y = centery[i] + radii[i]*sinf(2*PI*(float)k/(float)CIRCRES);
         glVertex3f(x, y, 0.0);
      }
      glEnd();
   }

   return 0;
}
