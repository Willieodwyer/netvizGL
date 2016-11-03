//
// Created by werl on 01/11/16.
//

#ifndef NETVIZGL_SIMPLEFORCEDIRECTED_H
#define NETVIZGL_SIMPLEFORCEDIRECTED_H

#include <GL/glew.h>
#include "Vertex.h"
#include "Graph.h"

class SimpleForceDirected {
 private:

  Graph *graph;

 public:
  SimpleForceDirected(Graph *g);

  void simpleAL();
};

#endif //NETVIZGL_SIMPLEFORCEDIRECTED_H
