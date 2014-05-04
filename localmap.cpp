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

#define PI 3.1415926535

//static float dist[20], angle[20];
static int N=20;
static bool initdone = false;

int robot::getlocalmap(map* MAP) {

   int i;

   if (!initdone++) {
      dist  = new float[20];
      angle = new float[20];
      std::cout << "allocated "
                << (sizeof(*dist) + sizeof(*angle))*N
                << " bytes for local mapping"
                << std::endl;
   }

   for (i = 0; i < N; i++)
      angle[i] = -2.0 + (float) i / (float) (N - 1) * 4.0;

   for (i = 0; i < N; i++)
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

   glLineWidth(2.5);
   glColor3f(1.0, 0.0, 0.0);
   for (i = 0; i < N; i++) {
      glBegin(GL_LINES);
      glVertex3f(x*CONV, y*CONV, 0.0);
      glVertex3f(x*CONV + dist[i]*cosf(angle[i] + dir - reldir)*CONV,
                 y*CONV + dist[i]*sinf(angle[i] + dir - reldir)*CONV,
                 0.0);
      glEnd();
   }

   return 0;
}
