//
// Created by werl on 11/02/17.
//

#ifndef NETVIZGL_NORMALIZEDDEGREECENTRALITY_H
#define NETVIZGL_NORMALIZEDDEGREECENTRALITY_H

#include "Centrality.h"

class DegreeCentrality : public Centrality{
 public:
  void calcApply(Graph *gr) override;
};

#endif //NETVIZGL_NORMALIZEDDEGREECENTRALITY_H
