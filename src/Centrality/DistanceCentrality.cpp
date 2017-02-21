//
// Created by werl on 12/02/17.
//

#include <cfloat>
#include "../../inc/Centrality/DistanceCentrality.h"

void DistanceCentrality::calcApply(Graph *gr) {
  if(gr) {
    //normalise
    double x = 0;
    double max = 0;
    double min = DBL_MAX;
    double r;
    double g;
    double b;
    double h;

    double xDist = 0;
    double yDist = 0;
    double dist = 0;

    Vertex *v, *u;
    vector<double> distances;

    for (int i = 0; i < gr->numVertices; ++i) {
      v = gr->vertices[i];
      for (int j = 0; j < gr->numVertices; ++j) {
        if (i == j) continue;
        u = gr->vertices[j];

        xDist = (v->posX - u->posX);
        yDist = (v->posY - u->posY);
        dist += sqrt((xDist * xDist) + (yDist * yDist));
      }
      if (dist > max)
        max = dist;
      if (dist < min)
        min = dist;

      distances.push_back(dist);
      dist = 0;
    }

//  char *digit = new char[64];
    for (int i = 0; i < gr->numVertices; ++i) {
      x = normalized(distances[i], min, max);
      h = (1 - x) * 240;

      HSVtoRGB(r, g, b, h, 1, 1);

//    sprintf(digit, "%lf", h);
      gr->vertices[i]->setColour(r, g, b);
//    gr->vertices[i]->setText(digit);
    }

//  delete (digit);
  }
}
