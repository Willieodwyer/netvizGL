//
// Created by william on 02/03/17.
//

#ifndef NETVIZGL_MULTIFORCE_H
#define NETVIZGL_MULTIFORCE_H

#include "Algorithm.h"
class MultiForce : public Algorithm{
 public:
  MultiForce(Graph *g);
  void apply() override;
  void initialPlacement() override;
  double area;
  double k;
  double W;
  double L;
  double t;
  void placement();
  double edgeIndex = 0;

  double energy1 = 0;
  double energy = 0;

  bool doPlace;

  vector<int*> newEdgeList;
  vector<int> seenVertices;
  Graph *temp;
};

#endif //NETVIZGL_MULTIFORCE_H
