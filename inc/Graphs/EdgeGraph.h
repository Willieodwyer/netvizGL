//
// Created by werl on 11/11/16.
//

#ifndef NETVIZGL_EDGEGRAPH_H
#define NETVIZGL_EDGEGRAPH_H

#include "Graph.h"
class EdgeGraph : public Graph {
 public:
  EdgeGraph(char *filePath);
  EdgeGraph(char *filePath, vector<int *> newEdgeList);
  virtual void draw();
  virtual void update();
 private:
 public:
  virtual ~EdgeGraph();
 private:
  virtual void read(char *filePath);
  bool validate(char *filePath);
};

#endif //NETVIZGL_EDGEGRAPH_H
