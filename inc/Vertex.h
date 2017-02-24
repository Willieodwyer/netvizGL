//
// Created by werl on 23/09/16.
//

#ifndef NETVIZGL_SPHERE_H
#define NETVIZGL_SPHERE_H

#include <cmath>
#include "Edge.h"
#include <vector>
#include <mutex>
#include <FTGL/ftgl.h>

using namespace std;
class Vertex {
 private:
  GLdouble colourR;
  GLdouble colourG;
  GLdouble colourB;

  GLuint *indices;
  GLint indIndex;

  GLdouble *vertices;
  GLdouble *colours;

  std::mutex mtx;

  vector<Edge *> lines;

  FTPixmapFont *font;

  GLdouble *pos;
 public:
  static const unsigned int rings = 12, sectors = 12;
  static constexpr double radius = .01;

  Vertex(GLdouble offsetx, GLdouble offsety, GLdouble offsetz);
  virtual ~Vertex();

  vector<Vertex *> attachedPoints;
  void attachPoint(Vertex *p);

  int degree = 0;
  int level;
  int vertexNumber = 0;

  GLdouble posX, posY, posZ;
  GLdouble force;
  GLdouble forceX, forceY, forceZ;
  GLdouble velocityX, velocityY, velocityZ;

  void setColour(GLdouble r, GLdouble g, GLdouble b);
  GLdouble *getColour(GLdouble *colours);

  void draw();
  void update();

  bool selected;
  bool isPointerOver(double x, double y, int width, int height);
  double getDepth();

  void *getScreenPosition(GLdouble *pos);
  void setPositionFromScreen(double x, double y);

  void drawText();
  void setText(const char *t);
  char *text;
};

#endif //NETVIZGL_SPHERE_H
