#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "robot.h"
#include "map.h"
#include <math.h>

void idle(void){
   glutPostRedisplay();
}

void move(void){
   float thetalen = 2.5;
   float r1,r2;
   float th, dth;
   int i, N = 20;
   float *arcx1 = (float*) calloc(2*N, sizeof(float));
   float *arcy1 = (float*) calloc(2*N, sizeof(float));
   float *arcx2 = arcx1 + N;
   float *arcy2 = arcy1 + N;

   r1 = 0.25; r2 = 0.75;
   dth = (thetalen - 0.0)/((float)(N-1));

   th = 0.0;
   for (i = 0; i < N; i++){
      arcx1[i] = r1*cosf(th);
      arcy1[i] = r1*sinf(th);
      th += dth;
   }
   th = 0.0;
   for (i = 0; i < N; i++){
      arcx2[i] = r2*cosf(th);
      arcy2[i] = r2*sinf(th);
      th += dth;
   }

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

   glFlush();
}

int main(int argc, char** argv){

   map *MAP = new map();
   robot rob;

   MAP->hello();

   delete MAP;

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("OpenGL Example");

   glutDisplayFunc(move);
//   glutKeyboardUpFunc(keyboardUp);
//   glutKeyboardFunc(keyboardDown);
   glutIdleFunc(idle);

   glutMainLoop();

   return 0;
}
