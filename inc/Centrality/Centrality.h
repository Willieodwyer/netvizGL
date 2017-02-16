//
// Created by werl on 11/02/17.
//

#ifndef NETVIZGL_CENTRALITY_H
#define NETVIZGL_CENTRALITY_H

#include "../Graphs/Graph.h"

class Centrality {
 public:
  virtual void calcApply(Graph *g) = 0;

  void HSVtoRGB(double &r, double &g, double &b, double h, double s, double v){
    int i;
    double f, p, q, t;
    if (s == 0) {
      // achromatic (grey)
      r = g = b = v;
      return;
    }
    h /= 60;            // sector 0 to 5

    i = (int) floor(h);

    f = h - i;            // factorial part of h
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));

    switch (i) {
      case 0:r = v;
        g = t;
        b = p;
        break;
      case 1:r = q;
        g = v;
        b = p;
        break;
      case 2:r = p;
        g = v;
        b = t;
        break;
      case 3:r = p;
        g = q;
        b = v;
        break;
      case 4:r = t;
        g = p;
        b = v;
        break;
      default:        // case 5:
        r = v;
        g = p;
        b = q;
        break;
    }
  }

  inline double normalized(double x, double max, double min) {
    return (x - min) / (max - min);
  }
};

#endif //NETVIZGL_CENTRALITY_H
