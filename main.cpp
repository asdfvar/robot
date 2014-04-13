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

map *MAP = new map();
robot rob(0.0, 0.0, 1.57);
int mode = 1;

void idle(void){

   rob.update();
//   std::cout << MAP->getdist(10.0, 10.0) << std::endl;
   rob.collide(MAP);

   glutPostRedisplay();
}

/********
 * move *
 ********/

void move(void){

   glClear(GL_COLOR_BUFFER_BIT);

   MAP->draw(rob, mode);
   rob.drawpath(mode);
   rob.drawrobot(mode);

   glFlush();
}

/*****************
 * keyboard Down *
 *****************/

void keyboardDown(unsigned char key, int x, int y){
   rob.move(key);

   // quit
   if (key == 'q'){
      delete MAP;
      std::cout << "program exit" << std::endl;
      exit(1);
   }
   else if (key == 'C')
      mode = 2;
   else if (key == 'c')
      mode = 1;
   else if (key == 'g')
      mode = 0;
   else if (key == '0')
      rob.setposxy(0.0, 0.0);
}

/***************
 * keyboard Up *
 ***************/

void keyboardUp(unsigned char key, int x, int y){
   rob.unmove(key);
}

/********
 * main *
 ********/

int main(int argc, char** argv){

   float x1[4],x2[4],y1[4],y2[4];
   float cx[3],cy[3],rad[3];

   x1[0] = 0.0; x1[1] = -0.5; x1[2] = -0.5; x1[3] = 0.5;
   y1[0] = 0.0; y1[1] = -0.5; y1[2] = 0.5; y1[3] = -0.5;
   x2[0] = 0.5; x2[1] = 0.0; x2[2] = 0.5; x2[3] = 0.5;
   y2[0] = 0.5; y2[1] = 1.0; y2[2] = -0.5; y2[3] = 0.5;

   MAP->loadlines(&x1[0], &y1[0], &x2[0], &y2[0], 4);

   cx[0] = 0.0; cx[1] = 0.5; cx[2] = -0.5;
   cy[0] = 0.0; cy[1] = 0.5; cy[2] = 0.5;;
   rad[0] = 0.2; rad[1] = 0.1; rad[2] = 0.3;

   MAP->loadcircles(&cx[0], &cy[0], &rad[0], 3);

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
   glutInitWindowSize(900, 900);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("OpenGL Example");

   glutDisplayFunc(move);
   glutKeyboardUpFunc(keyboardUp);
   glutKeyboardFunc(keyboardDown);
   glutIdleFunc(idle);

   glutMainLoop();

   return 0;
}
