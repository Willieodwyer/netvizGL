//
// Created by werl on 23/09/16.
//

#ifndef NETVIZGL_SPHERE_H
#define NETVIZGL_SPHERE_H

#include <cmath>
#include "Line.h"
#include <vector>
using namespace std;
class Point {
 public:
  static const unsigned int rings = 18, sectors = 18;
  static const double radius = .01;

  vector<Point *> attachedPoints;

  int pointIndex = 0;

  void attachPoint(Point *p);

  vector<Line *> lines;

  GLdouble colourR;
  GLdouble colourG;
  GLdouble colourB;

  Point(float OFFSETX, float OFFSETY, float OFFSETZ, int index);

  GLdouble offsetX, offsetY, offsetZ;

  GLuint *indices;
  GLint indIndex;

  virtual ~Point();

  void draw();

  void setColour(GLdouble r, GLdouble g, GLdouble b);

  GLdouble *getColour();

  GLdouble *vertices;
  GLdouble *colours;
};

#endif //NETVIZGL_SPHERE_H
