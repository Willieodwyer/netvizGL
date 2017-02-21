//
// Created by werl on 01/11/16.
//

#include <sys/time.h>
#include <zconf.h>
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

      GLdouble rsq = .25 * ((v->posX - u->posX) * (v->posX - u->posX)
          + (v->posY - u->posY) * (v->posY - u->posY));

      v->forceX += 10 * ((v->posX - u->posX) / rsq);
      v->forceY += 10 * ((v->posY - u->posY) / rsq);
    }

    for (int j = 0; j < graph->numVertices; ++j) {
      if (graph->adjacencyMatrix[i][j]) {
        u = graph->vertices[j];
        v->forceX += 4 * (u->posX - v->posX);
        v->forceY += 4 * (u->posY - v->posY);
      }
    }

    v->velocityX = (v->velocityX + v->forceX) * 0.01;
    v->velocityY = (v->velocityY + v->forceY) * 0.01;
  }

  for (int i = 0; i < graph->numVertices; ++i) {
    v = graph->vertices[i];
    v->posX += v->velocityX;
    v->posY += v->velocityY;
  }
}

SimpleForceDirected::SimpleForceDirected(Graph *g)
    : Algorithm(g) {
  initialPlacement();
}
void SimpleForceDirected::initialPlacement() {
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < graph->numVertices; ++j) {
    graph->vertices[j]->posX = ((double) rand()) / RAND_MAX * graph->numVertices - graph->numVertices / 2;
    graph->vertices[j]->posY = ((double) rand()) / RAND_MAX * graph->numVertices - graph->numVertices / 2;
    graph->vertices[j]->posZ = 0;
  }

  for (int i = 0; i < graph->numVertices; ++i) {
    for (int j = 0; j < graph->numVertices; ++j) {
      if (graph->vertices[i]->posX == graph->vertices[j]->posX && i != j
          && graph->vertices[i]->posY == graph->vertices[j]->posY)
        fprintf(stderr, "Warning: duplicate positions generated @ %d\n", i);
    }
  }
}



