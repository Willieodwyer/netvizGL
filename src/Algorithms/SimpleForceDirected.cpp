//
// Created by werl on 01/11/16.
//

#include "../../inc/Algorithms/SimpleForceDirected.h"
void SimpleForceDirected::apply() {

  Vertex *v;
  Vertex *u;

  for (int i = 0; i < graph->numVertices; ++i) {

    v = graph->vertices[i];
    v->forceX = 0;
    v->forceY = 0;

    for (int j = 0; j < graph->numVertices; ++j) {
      if (i == j) continue;

      u = graph->vertices[j];

      GLdouble rsq = ((v->posX - u->posX) * (v->posX - u->posX)
          + (v->posY - u->posY) * (v->posY - u->posY));

      v->forceX += 5 * ((v->posX - u->posX) / rsq);
      v->forceY += 5 * ((v->posY - u->posY) / rsq);
    }

    for (int j = 0; j < graph->numVertices; ++j) {
      if (graph->edges[i][j]) {
        u = graph->vertices[j];
        v->forceX += 2 * (u->posX - v->posX);
        v->forceY += 2 * (u->posY - v->posY);
        //fprintf(stderr, "PULL[%d][%d]\n", i,j);
      }
    }

    v->velocityX = (v->velocityX + v->forceX) * 0.1;
    v->velocityY = (v->velocityY + v->forceY) * 0.1;
  }

  for (int i = 0; i < graph->numVertices; ++i) {
    v = graph->vertices[i];
    v->posX += v->velocityX;
    v->posY += v->velocityY;
  }
}

SimpleForceDirected::SimpleForceDirected(Graph *g)
    : Algorithm(g) {
}



