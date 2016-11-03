//
// Created by werl on 23/09/16.
//

#include <cstdio>
#include "../inc/Vertex.h"

Vertex::Vertex(float offsetx, float offsety, float offsetz) {

  forceX = 0, forceY = 0, forceZ = 0;
  velocityX = 0, velocityY = 0, velocityZ = 0;
  posX = offsetx, posY = offsety, posZ = offsetz;
  colourR = 0, colourB = 0, colourG = 0;

  const GLfloat RINGS = (float) 1.0 / (rings - 1);
  const GLfloat SECTORS = (float) 1.0 / (sectors - 1);

  int r, s, vertIndex = 0, colIndex = 0;
  indIndex = 0;

  vertices = new GLdouble[rings * sectors * 3];
  colours = new GLdouble[rings * sectors * 3];

  for (r = 0; r < rings; r++) {
    for (s = 0; s < sectors; s++) {

      GLdouble x = posX + cos(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);
      GLdouble y = posY + sin(-M_PI_2 + M_PI * r * RINGS);
      GLdouble z = posZ + sin(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);

      vertices[vertIndex++] = x * radius;
      vertices[vertIndex++] = y * radius;
      vertices[vertIndex++] = z * radius;

      colours[colIndex] = colourR;
      colours[colIndex] = colourG;
      colours[colIndex] = colourB;
    }
  }

  indices = new GLuint[rings * sectors * 4];

  for (r = 0; r < rings - 1; r++)
    for (s = 0; s < sectors - 1; s++) {

      indices[indIndex++] = r * sectors + s;
      indices[indIndex++] = r * sectors + (s + 1);
      indices[indIndex++] = (r + 1) * sectors + (s + 1);
      indices[indIndex++] = (r + 1) * sectors + s;

    }
}

void Vertex::update() {
  const GLfloat RINGS = (float) 1.0 / (rings - 1);
  const GLfloat SECTORS = (float) 1.0 / (sectors - 1);

  int r, s, vertIndex = 0, colIndex = 0;
  indIndex = 0;

  for (r = 0; r < rings; r++) {
    for (s = 0; s < sectors; s++) {

      GLdouble x = posX + cos(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);
      GLdouble y = posY + sin(-M_PI_2 + M_PI * r * RINGS);
      GLdouble z = posZ + sin(2 * M_PI * s * SECTORS) * sin(M_PI * r * RINGS);

      vertices[vertIndex++] = x * radius;
      vertices[vertIndex++] = y * radius;
      vertices[vertIndex++] = z * radius;

      colours[colIndex] = colourR;
      colours[colIndex] = colourG;
      colours[colIndex] = colourB;
    }
  }

  for (r = 0; r < rings - 1; r++)
    for (s = 0; s < sectors - 1; s++) {

      indices[indIndex++] = r * sectors + s;
      indices[indIndex++] = r * sectors + (s + 1);
      indices[indIndex++] = (r + 1) * sectors + (s + 1);
      indices[indIndex++] = (r + 1) * sectors + s;

    }

  for (int i = 0; i < lines.size(); ++i) {
    lines[i]->posX1 = posX * Line::scale;
    lines[i]->posY1 = posY * Line::scale;
    lines[i]->posZ1 = posZ * Line::scale;

    lines[i]->posX2 = attachedPoints[i]->posX * Line::scale;
    lines[i]->posY2 = attachedPoints[i]->posY * Line::scale;
    lines[i]->posZ2 = attachedPoints[i]->posZ * Line::scale;

    lines[i]->update();
  }

}

void Vertex::draw() {

  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3, GL_DOUBLE, 0, this->vertices);

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glColorPointer(3, GL_DOUBLE, 0, NULL);
  glDrawElements(GL_QUADS, this->indIndex, GL_UNSIGNED_INT, this->indices);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glPolygonOffset(-2.5f, -2.5f);
  glColorPointer(3, GL_DOUBLE, 0, colours);
  glDrawElements(GL_QUADS, this->indIndex, GL_UNSIGNED_INT, this->indices);

  glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
  glDisableClientState(GL_COLOR_ARRAY);

  if (lines.size() > 0) {
    for (int i = 0; i < lines.size(); ++i) {
      lines[i]->draw();
    }
  }
}

Vertex::~Vertex() {

}

void Vertex::setColour(GLdouble R, GLdouble G, GLdouble B) {

  colourR = R;
  colourG = G;
  colourB = B;

  int colIndex = 0;

  for (int r = 0; r < rings; r++) {
    for (int s = 0; s < sectors; s++) {
      colours[colIndex++] = colourR;
      colours[colIndex++] = colourG;
      colours[colIndex++] = colourB;
    }
  }
}

GLdouble *Vertex::getColour() {
  GLdouble *ret = new GLdouble[3];
  ret[0] = colourR;
  ret[1] = colourG;
  ret[2] = colourB;
  return ret;
}

void Vertex::attachPoint(Vertex *p) {
  attachedPoints.push_back(p);
  Line *l = new Line(posX * 0.1, posY * 0.1, posZ * 0.1,
                     p->posX * 0.1, p->posY * 0.1, p->posZ * 0.1);
  //l->setColour(colourR,colourG,colourB,p->colourR,p->colourG,p->colourB);
  lines.push_back(l);
}
