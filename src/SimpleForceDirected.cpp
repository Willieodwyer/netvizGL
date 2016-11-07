//
// Created by werl on 01/11/16.
//

#include "../inc/SimpleForceDirected.h"
SimpleForceDirected::SimpleForceDirected(Graph *g) {
  graph = g;
}

void SimpleForceDirected::simpleAL() {

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

      v->forceX += 20 * ((v->posX - u->posX) / rsq);
      v->forceY += 20 * ((v->posY - u->posY) / rsq);

      //fprintf(stderr, "PUSH[%d][%d]\n", i,j);
    }

    for (int j = 0; j < graph->numVertices; ++j) {
      if (graph->edges[i][j]) {
        u = graph->vertices[j];
        v->forceX += 3.5 * (u->posX - v->posX);
        v->forceY += 3.5 * (u->posY - v->posY);
        //fprintf(stderr, "PULL[%d][%d]\n", i,j);
      }
    }

    v->velocityX = (v->velocityX + v->forceX) * 0.0085;
    v->velocityY = (v->velocityY + v->forceY) * 0.0085;
  }

  for (int i = 0; i < graph->numVertices; ++i) {
    v = graph->vertices[i];
    v->posX += v->velocityX;
    v->posY += v->velocityY;
  }
}



