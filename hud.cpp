#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>
#include "constants.h"

void identifier(float x, float y, float diameter) {

  extern float CONV;
  float radius = diameter/2.0;

  // draw identifier circle around robot

  glColor3ub(100, 100, 100);
  glBegin(GL_POLYGON);

  for (int i = 0; i < 40; i++) {
    glVertex3f(
      (x + radius*cosf(2*PI*(float)i/40.0))*CONV,
      (y + radius*sinf(2*PI*(float)i/40.0))*CONV,
      0.0);
  }

  glEnd();

}
