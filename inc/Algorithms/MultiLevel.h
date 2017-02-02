//
// Created by william on 30/01/17.
//

#ifndef NETVIZGL_MULTILEVEL_H
#define NETVIZGL_MULTILEVEL_H

#include "Algorithm.h"

class MultiLevel : public Algorithm {
 public:
  MultiLevel(Graph *g);

 private:
  int **matx;
  int **lists;
  vector<int *> ll;
  vector<int> degree;
  int **lists1;
  int **lists2;
  int *verts;
  double *force_x;
  double *force_y;
  bool ev = true;
  int level = 1;

  bool **mat;
  int **mat1;
  vector<char *> Alists;
  int com = 0;
  double hypotenuse = 0;
  double energy0 = 10E100;
  double energy1 = 0;
  double k = 0;
  double popu = 0;  //number of visited nodeas at the time
  bool **sh2;
  double c = 0.5;
  double progress = 0;
  double int_pr = 0;

  double x_cent = 0;
  double y_cent = 0;

  int *degree_met;
  double force = 0;
  double tol = 0; //tolerance, threshold = disp * root(nodes)
  double deg_met = 0;
  long main_run_time = 0;
  vector<int*> seen_links;
  double ch1 = 2;
  double ch2 = 10;

 public:
  void apply() override;
};

#endif //NETVIZGL_MULTILEVEL_H
