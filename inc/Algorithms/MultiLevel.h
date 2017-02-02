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
  int com = 0;

  double hypotenuse = 0;

  double energy0 = 10E100;
  double energy1 = 0;

  double k = 0;
  double completedVertices = 0;

  double int_pr = 0;
  int *degree_met;

  double force = 0;
  double tolerance = 0;

  vector<int *> seen_links;

  double ch1 = 2;
  double ch2 = 10;
 public:
  void apply() override;
  void calculateForces(int numV, int s);

  //Initial Values
  int linkIndex;
  double numVerticesF;
  double display;
  int base;
  int connected;
  int *ini;
  int iterations;
  double di;
  double ti;
  double ti_lev;
  double ti_rate;
  double k_rate;
  double rnd;
  bool fin;
};

#endif //NETVIZGL_MULTILEVEL_H
