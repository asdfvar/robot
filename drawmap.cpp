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

int map::draw(float relx, float rely, float reldir){

   int i,k;
   float x,y,tmp;

   /**************
    * draw lines *
    **************/

   for (i = 0; i < Nlines; i++){
      glLineWidth(2.5); 
      glColor3f(1.0, 1.0, 0.0);
      glBegin(GL_LINES);
        x = x1[i];
        y = y1[i];

        x -= relx;
        y -= rely;
        tmp = x*cosf(reldir) + y*sinf(reldir);
        y   = -x*sinf(reldir) + y*cosf(reldir);
        x = tmp;

        glVertex3f(x, y, 0.0);

        x = x2[i];
        y = y2[i];

        x -= relx;
        y -= rely;
        tmp = x*cosf(reldir) + y*sinf(reldir);
        y   = -x*sinf(reldir) + y*cosf(reldir);
        x = tmp;

        glVertex3f(x, y, 0.0);

      glEnd();
   }

   /****************
    * draw circles *
    ****************/

   for (i = 0; i < Ncircles; i++){
      glBegin(GL_POLYGON);
      for (k = 0; k < CIRCRES; k++){
         x = (centerx[i] + radii[i]*cosf(2.0*PI*(float)k/(float)CIRCRES))*CONV;
         y = (centery[i] + radii[i]*sinf(2.0*PI*(float)k/(float)CIRCRES))*CONV;

         x -= relx; y -= rely;
         tmp = x*cosf(reldir) + y*sinf(reldir);
         y   = -x*sinf(reldir) + y*cosf(reldir);
         x = tmp;

         glVertex3f(x, y, 0.0);
      }
      glEnd();
   }

   return 0;
}
