#include "robot.h"
#include "map.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include "constants.h"

class robot;
class map;

int robot::getlocalmap(map* MAP) {

   int i;

   for (i = 0; i < N_dist; i++)
      angle[i] = -2.0 + (float) i / (float) (N_dist - 1) * 4.0;

   for (i = 0; i < N_dist; i++)
      dist[i] = MAP->distance(posx, posy, angle[i] + dir);

   return 0;
}

int robot::drawlocalmap(float relx, float rely, float reldir) {

   int i;
   float x,y,tmp;

   x = posx - relx;
   y = posy - rely;

   tmp = x*cosf(reldir) + y*sinf(reldir);
   y = -x*sinf(reldir) + y*cosf(reldir);
   x = tmp;

   float deltadir = dir - reldir;

   glLineWidth(2.5);
   glColor3f(1.0, 0.0, 0.0);
   for (i = 0; i < N_dist; i++) {
      glBegin(GL_LINES);
      glVertex3f(x*CONV, y*CONV, 0.0);
      glVertex3f(x*CONV + dist[i]*cosf(angle[i] + deltadir)*CONV,
                 y*CONV + dist[i]*sinf(angle[i] + deltadir)*CONV,
                 0.0);
      glEnd();
   }

   return 0;
}
