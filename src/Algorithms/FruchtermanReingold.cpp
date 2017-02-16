//
// Created by werl on 10/02/17.
//

#include <sys/time.h>
#include <zconf.h>
#include "../../inc/Algorithms/FruchtermanReingold.h"
#include "../../inc/GLWindow.h"

FruchtermanReingold::FruchtermanReingold(Graph *g) : Algorithm(g) {
  W = 128;
  L = 72;
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
  }

  for (int i = 0; i < graph->numEdges; ++i) {
    v = graph->vertices[graph->edgeList[i][0]];
    u = graph->vertices[graph->edgeList[i][1]];

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

  for (int i = 0; i < graph->numVertices; ++i) {
    v = graph->vertices[i];
    v->posX += v->forceX * 0.0015;
    v->posY += v->forceY * 0.0015;
////    v->velocityX = min(t, max(-t, (v->velocityX + v->forceX)));
////    v->velocityY = min(t, max(-t, (v->velocityY + v->forceY)));
//
//    v->posX += (v->forceX / (abs(v->forceX))) * min(t, max(-t, (v->forceX)));
//    v->posY += (v->forceY / (abs(v->forceY))) * min(t, max(-t, (v->forceY)));

//    v->posX = min(4*W, max(-4*W, v->posX));
//    v->posY = min(4*L, max(-4*L, v->posY));
  }
  t *= .9;

}

void FruchtermanReingold::initialPlacement() {
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < graph->numVertices; ++j) {
    graph->vertices[j]->posX = ((double) rand()) / RAND_MAX * (W) - W / 2;
    graph->vertices[j]->posY = ((double) rand()) / RAND_MAX * (L) - L / 2;
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
