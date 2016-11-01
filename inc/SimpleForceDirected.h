//
// Created by werl on 01/11/16.
//

#ifndef NETVIZGL_SIMPLEFORCEDIRECTED_H
#define NETVIZGL_SIMPLEFORCEDIRECTED_H

#include <GL/glew.h>
#include "Point.h"
#include "Graph.h"

class SimpleForceDirected {
 private:
  const GLdouble REPULSIONCONST = 10000;
  const GLdouble ATTRACTION_CONST = 0.1;
  const GLdouble DEFAULT_DAMPING = 0.5;
  const GLint DEFAULT_SPRING_LENGTH = 100;
  const GLint DEFAULT_MAX_ITERATIONS = 500;
  Graph *_graph;

  GLdouble calculateRepulsionForce(Point x, Point y);

 public:
  SimpleForceDirected(Graph graph);
  void arrange();

};

#endif //NETVIZGL_SIMPLEFORCEDIRECTED_H
