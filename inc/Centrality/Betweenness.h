//
// Created by william on 13/03/17.
//

#ifndef NETVIZGL_BETWEENNESS_H
#define NETVIZGL_BETWEENNESS_H

#include "Centrality.h"
class Betweenness : public Centrality{
 public:
  void calcApply(Graph *g) override;
  int findDist(int v, int u, Graph *g);
};

#endif //NETVIZGL_BETWEENNESS_H
