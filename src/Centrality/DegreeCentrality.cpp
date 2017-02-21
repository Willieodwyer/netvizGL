//
// Created by werl on 11/02/17.
//

#include <cfloat>
#include "../../inc/Centrality/DegreeCentrality.h"

void DegreeCentrality::calcApply(Graph *gr) {
  if(gr) {
    //normalise
    double x = 0;
    double max = 0;
    double min = DBL_MAX;
    double r;
    double g;
    double b;
    double h;

    for (int i = 0; i < gr->numVertices; ++i) {
      if (gr->vertices[i]->degree > max)
        max = gr->vertices[i]->degree;

      if (gr->vertices[i]->degree < min)
        min = gr->vertices[i]->degree;
    }

//  char *digit = new char[64];
    for (int i = 0; i < gr->numVertices; ++i) {
      x = normalized(gr->vertices[i]->degree, max, min);

      h = (1 - x) * 240;

      HSVtoRGB(r, g, b, h, 1, 1);

//    sprintf(digit, "%lf", h);
      gr->vertices[i]->setColour(r, g, b);
//    gr->vertices[i]->setText(digit);
    }

//  delete (digit);
  }
}
