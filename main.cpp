#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "map.h"
#include <cmath>
#include <time.h>
#include "avoidance.h"
#include "constants.h"
#include "list.h"

float CONV = 1.0; // conversion from meters to screen units

#define DEBUG
bool dbg = false;

enum {MAN, AUT};

float gettime(void);

#define N_robots 4
map *MAP = new map();
robot rob[N_robots];
robot *jub = &rob[0];
int irob = 0;
int view_mode = FREE;
int control_mode = MAN;

float xview=0.0, yview=0.0, dirview=0.0;
float xold, yold;

float relx=0.0, rely=0.0, reldir=0.0;
int windowsizex=800, windowsizey=800;

list robots;

/********
 * idle *
 ********/

void idle(void) {

   int i;
   float dt;



   if (control_mode == AUT) {
     for (i = 0; i < N_robots; i++) {
       robots.get_robot()->autonomous();
       robots.set_next();
#if 0
       rob[i].autonomous();
#endif
     }
   }

   dt = gettime();

   for (i=0; i<N_robots; i++) {
      robots.get_robot()->update(dt);
      robots.get_robot()->collide(MAP);
      robots.get_robot()->getlocalmap(MAP);
      robots.set_next();

#if 0
      rob[i].update(dt);
      rob[i].collide(MAP);
      rob[i].getlocalmap(MAP);
#endif
   }

   if (view_mode == FREE) {
      reldir = dirview;
      relx   = xview;
      rely   = yview;
   } else if (view_mode == CNTRFIX) {
      reldir = robots.get_robot()->getdir() - 0.5*PI;
      relx   = robots.get_robot()->getposx();
      rely   = robots.get_robot()->getposy();
#if 0
      reldir = jub->getdir() - 0.5*PI;
      relx   = jub->getposx();
      rely   = jub->getposy();
#endif
   } else if (view_mode == CNTR) {
      reldir = 0.0;
      relx = robots.get_robot()->getposx();
      rely = robots.get_robot()->getposy();
#if 0
      relx   = jub->getposx();
      rely   = jub->getposy();
#endif
   } else {
      reldir = 0.0;
      relx   = 0.0;
      rely   = 0.0;
   }

   glutPostRedisplay();
}

/********
 * move *
 ********/

void move(void){

   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   MAP->draw(relx, rely, reldir);

   for (i=0; i<N_robots; i++) {

      robots.get_robot()->drawrobot(relx, rely, reldir);

#if 0
      rob[i].drawrobot(relx, rely, reldir);
#endif

   if (dbg){
      robots.get_robot()->drawlocalmap(relx, rely, reldir);
      robots.get_robot()->drawpath(relx, rely, reldir);
#if 0
      rob[i].drawlocalmap(relx, rely, reldir);
      rob[i].drawpath(relx, rely, reldir);
#endif

      if (control_mode == AUT)

         robots.get_robot()->drawautonomous(relx, rely, reldir);

#if 0
         rob[i].drawautonomous(relx, rely, reldir);
#endif

   }
   robots.set_next();
   }

   glFlush();
}

/*****************
 * keyboard Down *
 *****************/

void keyboardDown(unsigned char key, int x, int y){

   extern float CONV;

   robots.get_robot()->move(key);
#if 0
   jub->move(key);
#endif

   // quit
   if (key == 'q'){
      delete MAP;
      std::cout << "program exit" << std::endl;
      exit(1);
   }
   else if (key == 'C')
      view_mode = CNTRFIX;
   else if (key == 'c')
      view_mode = CNTR;
   else if (key == 'g')
      view_mode = FREE;
   else if (key == '0')
      robots.get_robot()->setposxy(0.0, 0.0, 0.0);
#if 0
      jub->setposxy(0.0, 0.0, 0.0);
#endif
   else if (key == 't')
      jub = &rob[++irob % N_robots];
   else if (key == 'T') {
      --irob;
      if (irob < 0) {irob += N_robots;}
      jub = &rob[irob % N_robots];
   } else if (key == 'o')
      dbg = 1 - dbg;

   if (key == 'A')
      control_mode = AUT;
   else if (key == 'M')
      control_mode = MAN;

   if (key == '-')
      CONV -= 0.2;
      if (CONV < 0.0) CONV = 0.0;
   else if (key == '=')
      CONV += 0.2;

}


/***************
 * keyboard Up *
 ***************/

void keyboardUp(unsigned char key, int x, int y) {

   int i;

   for (i=0; i<N_robots; i++) {

      robots.get_robot()->unmove(key);
#if 0
      jub->unmove(key);
#endif
   }
}

/***************
 * mouse click *
 ***************/

void mouseclick(int button, int state, int x, int y) {

/*
 *    button
 * GLUT_LEFT_BUTTON
 * GLUT_MIDDLE_BUTTON
 * GLUT_RIGHT_BUTTON
 *    state
 * GLUT_UP
 * GLUT_DOWN
 */

  extern float CONV;
  float xpos, ypos;

  xpos = x - windowsizex/2 + 0.5;
  xpos /= windowsizex/2/CONV;

  ypos = windowsizex/2 - y + 0.5;
  ypos /= windowsizey/2/CONV;

  if (button == 3)
     CONV += 0.05;
  else if (button == 4) {
     CONV -= 0.05;
     if (CONV < 0.0) CONV = 0.0;
  }

}

/****************
 * mouse motion *
 ****************/

void mouseMotion(int x, int y) {

  extern float CONV;
  float xpos, ypos;
  float dx,dy;

  xpos = x - windowsizex/2 + 0.5;
  xpos /= windowsizex/2;

  ypos = windowsizex/2 - y + 0.5;
  ypos /= windowsizey/2;

  dx = xpos - xold;
  dy = ypos - yold;

  xold = xpos;
  yold = ypos;

  xview -= dx/CONV;
  yview -= dy/CONV;

}

/************************
 * passive mouse motion *
 ************************/

void mousePassive(int x, int y) {

  float xpos, ypos;

  xpos = x - windowsizex/2 + 0.5;
  xpos /= windowsizex/2;

  ypos = windowsizex/2 - y + 0.5;
  ypos /= windowsizey/2;

  xold = xpos;
  yold = ypos;

}

/********
 * main *
 ********/

int main(int argc, char** argv){

   float x1[6],x2[6],y1[6],y2[6];
   float cx[1],cy[1],rad[1];

   x1[0] = 0.5; x1[1] = 0.5; x1[2] = -1.0;
   y1[0] = 0.5; y1[1] = 0.5; y1[2] = -1.0;
   x2[0] = -0.5; x2[1] = 0.5; x2[2] = -1.0;
   y2[0] = 0.5; y2[1] = -0.5; y2[2] = 1.0;

   x1[3] = -1.0; x1[4] = 1.0; x1[5] = -1.0;
   y1[3] = 1.0; y1[4] = 1.0; y1[5] = -1.0;
   x2[3] = 1.0; x2[4] = 1.0; x2[5] = 1.0;
   y2[3] = 1.0; y2[4] = -1.0; y2[5] = -1.0;

   MAP->loadlines(x1, y1, x2, y2, 6);

   cx[0] = -1.0;
   cy[0] = -1.0;
   rad[0] = 0.4;

   MAP->loadcircles(cx, cy, rad, 1);

   rob[0].setposxy(0.0, 0.0, 0.0);


   robots.append(new robot);
   robots.append(new robot);
   robots.append(new robot);
   robots.append(new robot);
   robots.print();

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
   glutInitWindowSize(windowsizex, windowsizey);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Robut");

   glutDisplayFunc(move);
   glutKeyboardUpFunc(keyboardUp);
   glutKeyboardFunc(keyboardDown);
   glutMouseFunc(mouseclick);
   glutPassiveMotionFunc(mousePassive);
   glutMotionFunc(mouseMotion);
   glutIdleFunc(idle);

   glutMainLoop();

   return 0;
}
