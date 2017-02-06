//
// Created by william on 30/01/17.
//

#ifndef NETVIZGL_MULTILEVEL_H
#define NETVIZGL_MULTILEVEL_H

#include "Algorithm.h"

class MultiLevel : public Algorithm {
 public:
  MultiLevel(Graph *g);

  int **lists;
  vector<Vertex *>visitedVertices; //visited nodes // If equal to zero -> unvisited

  double *force_x;
  double *force_y;

  int level = 1;

  double energy0 = 10E100;
  double energy1 = 0;

  double completedVertices = 0;

  double force = 0;

  vector<int *> seenLinks;
 public:
  void apply() override;
  void calcApplyForces();

  //Initial Values
  int edgeIndex;
  double numVerticesF;
  int baseEdge;
  int connectedEdge;
  int iterations;
  bool fin;
};

#endif //NETVIZGL_MULTILEVEL_H