//
// Created by werl on 11/11/16.
//

#ifndef NETVIZGL_ADJACENCYGRAPH_H
#define NETVIZGL_ADJACENCYGRAPH_H

#include "Graph.h"

class AdjacencyGraph : public Graph {
 public:
  AdjacencyGraph(const char *filePath);
  virtual void draw();
  virtual void update();
 private:
  virtual void read(const char *filePath);
};

#endif //NETVIZGL_ADJACENCYGRAPH_H
