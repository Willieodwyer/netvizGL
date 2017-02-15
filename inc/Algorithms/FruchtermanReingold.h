//
// Created by werl on 10/02/17.
//

#ifndef NETVIZGL_FRUCHTERMANREINGOLD_H
#define NETVIZGL_FRUCHTERMANREINGOLD_H

#include "Algorithm.h"
#include <sys/time.h>
#include <zconf.h>

class FruchtermanReingold : public Algorithm {
 public:
  FruchtermanReingold(Graph *g);
  void apply() override;
  void initialPlacement() override;
  double area;
  double k;
  double W;
  double L;
  double t;
};

#endif //NETVIZGL_FRUCHTERMANREINGOLD_H
