#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "map.h"
#include <math.h>

robot rob(0.0, 0.0, 1.57);

void idle(void){
   rob.update(0.04);
   glutPostRedisplay();
}

/********
 * move *
 ********/

void move(void){
   glClear(GL_COLOR_BUFFER_BIT);

   rob.drawpath();
   rob.drawrobot();

   glFlush();
}

/*****************
 * keyboard Down *
 *****************/

void keyboardDown(unsigned char key, int x, int y){
   rob.move(key);
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

   map *MAP = new map();

   MAP->hello();

   delete MAP;

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("OpenGL Example");

   glutDisplayFunc(move);
   glutKeyboardUpFunc(keyboardUp);
   glutKeyboardFunc(keyboardDown);
   glutIdleFunc(idle);

   glutMainLoop();

   return 0;
}
