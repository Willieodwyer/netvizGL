//
// Created by werl on 29/09/16.
//

#include "../inc/Line.h"
#include "../inc/Vertex.h"

const double Line::scale = Vertex::radius * 10;

Line::Line(GLdouble X1, GLdouble Y1, GLdouble Z1, GLdouble X2, GLdouble Y2, GLdouble Z2) {

  posX1 = X1;
  posY1 = Y1;
  posZ1 = Z1;
  posX2 = X2;
  posY2 = Y2;
  posZ2 = Z2;

  colors = new GLfloat[6];
  for (int i = 0; i < 6; ++i) {
    colors[i] = 0;
  }
  vertices = new GLdouble[6];
  vertices[0] = X1 * scale;
  vertices[1] = Y1 * scale;
  vertices[2] = Z1 * scale;
  vertices[3] = X2 * scale;
  vertices[4] = Y2 * scale;
  vertices[5] = Z2 * scale;
}

void Line::update() {
  vertices[0] = posX1 * scale;
  vertices[1] = posY1 * scale;
  vertices[2] = posZ1 * scale;
  vertices[3] = posX2 * scale;
  vertices[4] = posY2 * scale;
  vertices[5] = posZ2 * scale;
}

Line::~Line() {
  delete vertices;
}

void Line::draw() {

  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, colors);

  glVertexPointer(3, GL_DOUBLE, 0, this->vertices);

  glDrawArrays(GL_LINES, 0, 2);

  glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
  glDisableClientState(GL_COLOR_ARRAY);
}
void Line::setColour(GLfloat r, GLfloat g, GLfloat b, GLfloat r2, GLfloat g2, GLfloat b2) {
  colors[0] = r;
  colors[1] = g;
  colors[2] = b;
  colors[3] = r2;
  colors[4] = b2;
  colors[5] = g2;
}
