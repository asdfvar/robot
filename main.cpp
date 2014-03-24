#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "map.h"
#include <math.h>

float *mem = (float*) calloc(80, sizeof(float));
float mm2win = 0.0001; // conversion factor to go from mm to 1 unit
robot rob(0.2, 0.3, 1.0);

void idle(void){
   glutPostRedisplay();
}

void move(void){
   int i,N=20;
   float *arcx1 = mem;
   float *arcy1 = mem + N;
   float *arcx2 = mem + 2*N;
   float *arcy2 = mem + 3*N;

   rob.drawpath(arcx1, arcy1, arcx2, arcy2, N);

   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glColor3ub(255, 255, 255);
   glTranslatef(0.0, 0.0, 0.0);
   for (i = 0; i < N-1; i++){
      glBegin(GL_POLYGON);
      glVertex3f(arcx1[i], arcy1[i], 0.0);
      glVertex3f(arcx1[i+1], arcy1[i+1], 0.0);
      glVertex3f(arcx2[i+1], arcy2[i+1], 0.0);
      glVertex3f(arcx2[i], arcy2[i], 0.0);
      glEnd();
   }
   glPopMatrix();

   rob.drawrobot();

   glFlush();
}

void keyboardDown(unsigned char key, int x, int y){

}

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
//   glutKeyboardUpFunc(keyboardUp);
   glutKeyboardFunc(keyboardDown);
   glutIdleFunc(idle);

   glutMainLoop();

   return 0;
}
