//
// Created by werl on 11/11/16.
//

#ifndef NETVIZGL_ALGORITHM_H
#define NETVIZGL_ALGORITHM_H
#include "../Graphs/Graph.h"

class Algorithm {
 public:
  Algorithm(Graph *g) {
    graph = g;
  }
  virtual void apply() = 0;

  Graph *graph;
};

#endif //NETVIZGL_ALGORITHM_H
