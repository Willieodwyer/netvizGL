//
// Created by werl on 12/02/17.
//

#ifndef NETVIZGL_DISTANCECENTRALITY_H
#define NETVIZGL_DISTANCECENTRALITY_H

#include "Centrality.h"

class DistanceCentrality : public Centrality{
 public:
  void calcApply(Graph *g) override;
};

#endif //NETVIZGL_DISTANCECENTRALITY_H
