#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "map.h"
#include <math.h>
#include <time.h>
#include "avoidance.h"

#define PI 3.1415926

float gettime(void);

int N_robots=1;
map *MAP = new map();
robot rob[1];
robot *jub = &rob[0];
int irob = 0;
int mode = 1;

float relx=0.0, rely=0.0, reldir=0.0;

avoidance avi;

/********
 * idle *
 ********/

void idle(void){

   int i;
   float dt;

   dt = gettime();
   for (i=0; i<N_robots; i++) {
      rob[i].update(dt);
      rob[i].collide(MAP);
      rob[i].getlocalmap(MAP);
   }

   if (mode == AUT)
      avi.action(jub);
avi.action(jub);

   if (mode == FREE) {
      reldir = 0.0;
      relx   = 0.0;
      rely   = 0.0;
   } else if (mode == CNTRFIX) {
      reldir = jub->getdir();
      relx   = jub->getposx();
      rely   = jub->getposy();
   } else if (mode == CNTR) {
      reldir = 0.0;
      relx   = jub->getposx();
      rely   = jub->getposy();
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

   MAP->draw(relx, rely, reldir - 0.5*PI);

   for (i=0; i<N_robots; i++) {
      rob[i].drawpath(relx, rely, reldir - 0.5*PI);
      rob[i].drawrobot(relx, rely, reldir - 0.5*PI);
      rob[i].drawlocalmap(relx, rely, reldir - 0.5*PI);
   }

   glFlush();
}

/*****************
 * keyboard Down *
 *****************/

void keyboardDown(unsigned char key, int x, int y){

   jub->move(key);

   // quit
   if (key == 'q'){
std::cout << "about to delete" << std::endl;
      delete MAP;
      std::cout << "program exit" << std::endl;
      exit(1);
   }
   else if (key == 'C')
      mode = CNTRFIX;
   else if (key == 'c')
      mode = CNTR;
   else if (key == 'g')
      mode = FREE;
   else if (key == '0')
      jub->setposxy(0.0, 0.0, 0.0);
   else if (key == 't')
      jub = &rob[++irob % N_robots];
   else if (key == 'T') {
      --irob;
      if (irob < 0) {irob += N_robots;}
      jub = &rob[irob % N_robots];
   } else if (key == 'A')
      mode = AUT;

}


/***************
 * keyboard Up *
 ***************/

void keyboardUp(unsigned char key, int x, int y){

   int i;

   for (i=0; i<N_robots; i++) {
      jub->unmove(key);
   }
}

/********
 * main *
 ********/

int main(int argc, char** argv){

   float x1[4],x2[4],y1[4],y2[4];
   float cx[3],cy[3],rad[3];

   x1[0] = 0.5; x1[1] = -0.5;
   y1[0] = 0.5; y1[1] = -0.5;
   x2[0] = 0.5; x2[1] = 0.0;
   y2[0] = -0.5; y2[1] = 1.0;

   MAP->loadlines(&x1[0], &y1[0], &x2[0], &y2[0], 2);

   cx[0] = -0.5; cx[1] = 0.5; cx[2] = -0.5;
   cy[0] = 0.0; cy[1] = 0.5; cy[2] = 0.5;;
   rad[0] = 0.2; rad[1] = 0.1; rad[2] = 0.3;

   MAP->loadcircles(&cx[0], &cy[0], &rad[0], 3);

   rob[0].setposxy(0.0, 0.0, 0.0);

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
   glutInitWindowSize(900, 900);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Robut");

   glutDisplayFunc(move);
   glutKeyboardUpFunc(keyboardUp);
   glutKeyboardFunc(keyboardDown);
   glutIdleFunc(idle);

   glutMainLoop();

   return 0;
}
