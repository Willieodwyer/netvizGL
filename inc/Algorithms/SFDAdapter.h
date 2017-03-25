//
// Created by werl on 25/03/17.
//

#ifndef NETVIZGL_SFDADAPTER_H
#define NETVIZGL_SFDADAPTER_H

#include "Algorithm.h"
#include "SimpleForceDirected.h"
class SFDAdapter : public Algorithm {
 private:
  SimpleForceDirected *adaptee;
 public:
  SFDAdapter(Graph *g) : Algorithm(g) {
    //Code for converting into specific representation if needed.
    adaptee = new SimpleForceDirected(g);
  }
  void apply() override {
    adaptee->calculate();
  }
  void initialPlacement() override {
    adaptee->place();
  }

};

#endif //NETVIZGL_SFDADAPTER_H
