//
// Created by werl on 01/11/16.
//

#ifndef NETVIZGL_SIMPLEFORCEDIRECTED_H
#define NETVIZGL_SIMPLEFORCEDIRECTED_H
#include "../Graphs/Graph.h"
class SimpleForceDirected {
 private:
  Graph *graph;
 public:
  SimpleForceDirected(Graph *g);
  void calculate();
  void place();
};

#endif //NETVIZGL_SIMPLEFORCEDIRECTED_H
