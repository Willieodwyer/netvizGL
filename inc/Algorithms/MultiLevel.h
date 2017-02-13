//
// Created by william on 30/01/17.
//

#ifndef NETVIZGL_MULTILEVEL_H
#define NETVIZGL_MULTILEVEL_H

#include "Algorithm.h"

class MultiLevel : public Algorithm {
 public:
  MultiLevel(Graph *g);
  int *visitedVertices; //visited nodes // If equal to zero -> unvisited
  int level = 1;
  double energy0 = 10E100;
  double energy1 = 0;
 public:
  void apply() override;
  void calcApplyForces();
  void initialPlacement();

  //Initial Values
  int edgeIndex;
  double numVerticesF;
  int iterations;
  bool fin;

  void placement();
  int population;
  double k;
  double cooling;
  double temperature;

  double max_x;
  double min_x;
  double max_y;
  double min_y;
  double diagonal;
  double rFactor;
  double aFactor;
  double alpha;
  bool scaleOnce;
  bool done;
  int t;
  double tolerance;
  double displacement;
  void updateDiagonal();
  void updateCooling();
  void updateK();
  void updateTemperature();
};

#endif //NETVIZGL_MULTILEVEL_H