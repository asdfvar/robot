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

void identifier(float x, float y, float diameter);

float CONV = 1.0; // conversion from meters to screen units

bool dbg = false;

enum {MAN, AUT};

float gettime(void);

map *MAP = new map();
int irob = 0;
int view_mode = FREE;
int control_mode = MAN;

float xview=0.0, yview=0.0, dirview=0.0;
float xold, yold;

float relx=0.0, rely=0.0, reldir=0.0;
int windowsizex=800, windowsizey=800;

list jub;

/********
 * idle *
 ********/

void idle(void) {

   int i;
   float dt;

   if (control_mode == AUT) {
     for (i = 0; i < jub.N; i++) {
       jub.get_robot()->autonomous();
       jub.set_next();
     }
   }

   dt = gettime();

   for (i=0; i<jub.N; i++) {
      jub.get_robot()->update(dt);
      jub.get_robot()->collide(MAP);
      jub.get_robot()->getlocalmap(MAP);
      jub.set_next();
   }

   if (view_mode == FREE) {
      reldir = dirview;
      relx   = xview;
      rely   = yview;
   } else if (view_mode == CNTRFIX) {
      reldir = jub.get_robot()->getdir() - 0.5*PI;
      relx   = jub.get_robot()->getposx();
      rely   = jub.get_robot()->getposy();
   } else if (view_mode == CNTR) {
      reldir = 0.0;
      relx = jub.get_robot()->getposx();
      rely = jub.get_robot()->getposy();
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

void move(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   MAP->draw(relx, rely, reldir);

   // draw the circle around the robot

   if (view_mode == CNTR)
     identifier(0.0, 0.0, 0.125);
   else if (view_mode == CNTRFIX)
     identifier(0.0, 0.0, 0.125);
   else if (view_mode == FREE)
     identifier(
       jub.get_robot()->getposx(),
       jub.get_robot()->getposy(),
       0.125);

   for (i=0; i<jub.N; i++) {

      jub.get_robot()->drawrobot(relx, rely, reldir);

   if (dbg){
      jub.get_robot()->drawlocalmap(relx, rely, reldir);
      jub.get_robot()->drawpath(relx, rely, reldir);

      if (control_mode == AUT)

         jub.get_robot()->drawautonomous(relx, rely, reldir);

   }
   jub.set_next();
   }

   glutSwapBuffers ();
}

/*****************
 * keyboard Down *
 *****************/

void keyboardDown(unsigned char key, int x, int y){

   extern float CONV;

   jub.get_robot()->move(key);

   // quit
switch (key) {
   case 'q':
      delete MAP;
      MAP = 0;
      jub.clear();
      std::cout << "program exit" << std::endl;
      exit(1);
      break;
   case 'C':
      view_mode = CNTRFIX;
      break;
   case 'c':
      view_mode = CNTR;
      break;
   case 'g':
      view_mode = FREE;
      break;
   case '0':
      jub.get_robot()->setposxy(0.0, 0.0, 0.0);
      break;
   case 't':
      jub.set_next();
      break;
   case 'T':
      jub.set_prev();
      break;
   case 'n':
      jub.append(new robot);
      break;
   case 'b':
      jub.remove();
      break;
   case 'o':
      dbg = 1 - dbg;
      break;
   case 'A':
      control_mode = AUT;
      break;
   case 'M':
      control_mode = MAN;
      break;
   case '-':
      CONV -= 0.2;
      if (CONV < 0.01) CONV = 0.01;
      break;
   case '=':
      CONV += 0.2;
      break;
}

}


/***************
 * keyboard Up *
 ***************/

void keyboardUp(unsigned char key, int x, int y) {

   int i;

   for (i=0; i<jub.N; i++) {

      jub.get_robot()->unmove(key);
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
     if (CONV < 0.01) CONV = 0.01;
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

   jub.append(new robot);
   jub.print();

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
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
