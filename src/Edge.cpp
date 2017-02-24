//
// Created by werl on 29/09/16.
//

#include "../inc/Edge.h"
#include "../inc/Vertex.h"

const double Edge::scale = Vertex::radius * 10;

Edge::Edge(GLdouble X1, GLdouble Y1, GLdouble Z1, GLdouble X2, GLdouble Y2, GLdouble Z2) {

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

  text = new char[64];
  strcpy(text, "default String");
  font = new FTGLPixmapFont("../Fonts/arial.ttf");
  if (font->Error())
    fprintf(stderr, "Err");
  font->FaceSize(12);
}

void Edge::update() {
  vertices[0] = posX1 * scale;
  vertices[1] = posY1 * scale;
  vertices[2] = posZ1 * scale;
  vertices[3] = posX2 * scale;
  vertices[4] = posY2 * scale;
  vertices[5] = posZ2 * scale;
}

Edge::~Edge() {
  delete vertices;
}

void Edge::draw() {

  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, colors);

  glVertexPointer(3, GL_DOUBLE, 0, this->vertices);

  glDrawArrays(GL_LINES, 0, 2);

  glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
  glDisableClientState(GL_COLOR_ARRAY);
}

void Edge::drawText() {
  if (strlen(text) < 1)
    return;

  glPixelTransferf(GL_RED_BIAS, -1.0f);
  glPixelTransferf(GL_GREEN_BIAS, -1.0f);
  glPixelTransferf(GL_BLUE_BIAS, -1.0f);

  GLdouble *basePos = new GLdouble[3];
  GLdouble *connectPos = new GLdouble[3];
  base->getScreenPosition(basePos);
  connect->getScreenPosition(connectPos);

  double midX = basePos[0] + connectPos[0];
  midX = midX / 2;

  double midY = basePos[1] + connectPos[1];
  midY = midY / 2;

  double midZ = basePos[2] + connectPos[2];
  midZ = midZ / 2;

  font->Render(text, -1, FTPoint(midX + 5, midY + 5, midZ));

  delete basePos;
  delete connectPos;
}

void Edge::setColour(GLfloat r, GLfloat g, GLfloat b, GLfloat r2, GLfloat g2, GLfloat b2) {
  colors[0] = r;
  colors[1] = g;
  colors[2] = b;
  colors[3] = r2;
  colors[4] = b2;
  colors[5] = g2;
}
