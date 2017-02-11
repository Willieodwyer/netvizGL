//
// Created by werl on 10/02/17.
//

#include <sys/time.h>
#include <zconf.h>
#include "../../inc/Algorithms/FruchtermanReingold.h"
#include "../../inc/GLWindow.h"

FruchtermanReingold::FruchtermanReingold(Graph *g) : Algorithm(g) {
  W = 32;
  L = 18;
  area = W * L;
  k = sqrt(area / (double) graph->numVertices);
  t = graph->numVertices;
  initialPlacement();
}

void FruchtermanReingold::apply() {
  static double maxV = 0;
  Vertex *v;
  Vertex *u;

  for (int i = 0; i < graph->numVertices; ++i) {
    v = graph->vertices[i];
    v->forceX = 0;
    v->forceY = 0;

    for (int j = 0; j < graph->numVertices; ++j) {
      if (i == j) continue;

      u = graph->vertices[j];
      double xDist = (v->posX - u->posX);
      double yDist = (v->posY - u->posY);
      double dist = sqrt((xDist * xDist) + (yDist * yDist));

      if (dist < 0.00000000002) dist = 0.00000000002;

      double repulsion = k * k / dist;
      v->forceX += xDist / dist * repulsion;
      v->forceY += yDist / dist * repulsion;
    }

    for (int j = 0; j < graph->numVertices; ++j) {
      if (graph->adjacencyMatrix[i][j]) {
        u = graph->vertices[j];
        double xDist = (v->posX - u->posX);
        double yDist = (v->posY - u->posY);
        double dist = sqrt((xDist * xDist) + (yDist * yDist));

        if (dist < 0.00000000002) dist = 0.00000000002;

        double attraction = dist * dist / k;

        v->forceX -= xDist / dist * attraction;
        v->forceY -= yDist / dist * attraction;

        u->forceX += xDist / dist * attraction;
        u->forceY += yDist / dist * attraction;
      }
    }

    v->velocityX = min(t, max(-t, (v->velocityX + v->forceX)));
    v->velocityY = min(t, max(-t, (v->velocityY + v->forceY)));
  }

  for (int i = 0; i < graph->numVertices; ++i) {
    v = graph->vertices[i];
    v->posX += v->velocityX;
    v->posX = min(256.0, max(-256.0, v->posX));
    v->posY += v->velocityY;
    v->posY = min(144.0, max(-144.0, v->posY));
  }
    t *= .99;


}

void FruchtermanReingold::initialPlacement() {
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < graph->numVertices; ++j) {
    graph->vertices[j]->posX = ((double) rand()) / RAND_MAX * (2 * W) - W;
    graph->vertices[j]->posY = ((double) rand()) / RAND_MAX * (2 * L) - L;
    graph->vertices[j]->posZ = 0;
    graph->vertices[j]->setColour(((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)));
  }

  for (int i = 0; i < graph->numVertices; ++i) {
    for (int j = 0; j < graph->numVertices; ++j) {
      if (graph->vertices[i]->posX == graph->vertices[j]->posX && i != j
          && graph->vertices[i]->posY == graph->vertices[j]->posY)
        fprintf(stderr, "Warning: duplicate positions generated @ %d\n", i);
    }
  }
}
