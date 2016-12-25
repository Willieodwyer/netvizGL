//
// Created by werl on 15/11/16.
//

#include "../inc/Menu.h"

Menu::Menu(GLfloat X1, GLfloat Y1, GLfloat X2, GLfloat Y2) : X1(X1), Y1(Y1), X2(X2), Y2(Y2) {

}

void Menu::draw() {
  glPushMatrix();
  glDisable(GL_CULL_FACE);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glTranslatef(0.0, 0.0, .1);

  glBegin(GL_POLYGON);

  glColor3f(1.0f, 1.0f, 1.0f);               /* purple */

  const GLfloat z = -1;
  glVertex3f(X1, Y1, z);       /* NE */
  glVertex3f(X1, Y2, z);       /* NW */
  glVertex3f(X2, Y2, z);       /* SW */
  glVertex3f(X2, Y1, z);       /* SE */

  glEnd();

  glPopMatrix();

  return;
}
