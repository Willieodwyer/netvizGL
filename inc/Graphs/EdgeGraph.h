//
// Created by werl on 11/11/16.
//

#ifndef NETVIZGL_EDGEGRAPH_H
#define NETVIZGL_EDGEGRAPH_H

#include "Graph.h"
class EdgeGraph : public Graph {
 public:
  EdgeGraph(char *filePath);
  virtual void draw();
  virtual void update();
 private:
  virtual void read(const char *filePath);
};

#endif //NETVIZGL_EDGEGRAPH_H
