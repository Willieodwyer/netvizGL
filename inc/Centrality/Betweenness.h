//
// Created by william on 13/03/17.
//

#ifndef NETVIZGL_BETWEENNESS_H
#define NETVIZGL_BETWEENNESS_H

#include "Centrality.h"
class Betweenness : public Centrality {
 public:
  double *vals;
  vector<vector<int>> tree;
  void calcApply(Graph *g) override;
  void buildTree(Graph *g);
  void BFS(Graph *g, int v, int u);
};

#endif //NETVIZGL_BETWEENNESS_H
