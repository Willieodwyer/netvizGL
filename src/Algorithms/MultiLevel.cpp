//
// Created by william on 30/01/17.
//

#include <zconf.h>
#include <sys/time.h>
#include "../../inc/Algorithms/MultiLevel.h"

MultiLevel::MultiLevel(Graph *g)
    : Algorithm(g) {
  edgeIndex = 0; // First edgeIndex or random edgeIndex
  level = 1; //Level of vertices
  numVerticesF = (double) graph->numVertices;
  population = 2;
  iterations = 0;
  fin = false;

  visitedVertices = new int[graph->numVertices];
  for (int i = 0; i < graph->numVertices; ++i) {
    visitedVertices[i] = 0;
  }

  initialPlacement();
  k = 0;
  cooling = 0.99;
  temperature = 0.1;
  alpha = 0.5;

  max_x = 1280;
  max_y = 720;
  min_x = -1280;
  min_y = -720;

  scaleOnce = false;
  done = false;
  t = 0;
  tolerance = 0.1;
  displacement = 10.0 / numVerticesF;
}

void MultiLevel::apply() {
  if (!fin) {
    if (edgeIndex < (graph->numEdges)) {
      placement();
    }

    k = alpha / ((population));

    while (abs(energy1 - energy0) < tolerance * displacement) {
      energy1 = 0;
      calcApplyForces();
      temperature = temperature * cooling;
      alpha = alpha * cooling;
    }

    energy0 = energy1;
    temperature = .1;

    if (edgeIndex == graph->numEdges) {
      scaleOnce = true;
      fin = true;
    }

    if (fin)
      fprintf(stderr, "Finished\n");
    t++;
    fprintf(stderr, "LEVEL - %d\n", level);
  }
  if (scaleOnce && !done) {
    for (int i = 0; i < graph->numVertices; ++i) {
      graph->vertices[i]->posX = graph->vertices[i]->posX * (100);
      graph->vertices[i]->posY = graph->vertices[i]->posY * (100);
      done = true;
    }
  }
}

void MultiLevel::calcApplyForces() {
  rFactor = sqrt(numVerticesF);
  aFactor = rFactor * 5;


  //fprintf(stderr, "CALC FORCES\n");

  if (diagonal < 0.1) {
    rFactor = rFactor * (0.1);
    aFactor = aFactor * (0.1);
  }

  for (int j = t; j < graph->numEdges; j++) {
    int v = graph->edgeList[j][0]; // List of the EDge list that you have
    int u = graph->edgeList[j][1];

    if (visitedVertices[v] && visitedVertices[u]) {

      double rep = 0;
      double att = 0;
      double d = abs(graph->vertices[v]->posX - graph->vertices[u]->posX)
          + abs(graph->vertices[v]->posY - graph->vertices[u]->posY);

      if (d < 0.00000000002) d = 0.00000000002;

      double cos = ((graph->vertices[u]->posX - graph->vertices[v]->posX) / d);
      double sin = ((graph->vertices[u]->posY - graph->vertices[v]->posY) / d);

      rep = (k * k) / -d;  //Takes care of the distances making sure they're not small
      att = (d * d) / k;

      graph->vertices[v]->force = rep + att;
      graph->vertices[u]->force = rep + att;

      //V
      if (graph->vertices[v]->force > 0
          && graph->vertices[v]->force > diagonal / rFactor)
        graph->vertices[v]->force = diagonal / rFactor;

      else if (graph->vertices[v]->force < 0
          && abs(graph->vertices[v]->force) > diagonal / aFactor)
        graph->vertices[v]->force = -diagonal / aFactor;

      //U
      if (graph->vertices[u]->force > 0
          && graph->vertices[u]->force > diagonal / rFactor)
        graph->vertices[u]->force = diagonal / rFactor;

      else if (graph->vertices[u]->force < 0
          && abs(graph->vertices[u]->force) > diagonal / aFactor)
        graph->vertices[u]->force = -diagonal / aFactor;

      graph->vertices[v]->posX += graph->vertices[v]->force * cos * temperature;
      graph->vertices[v]->posY += graph->vertices[v]->force * sin * temperature;

      graph->vertices[u]->posX -= graph->vertices[u]->force * cos * temperature;
      graph->vertices[u]->posY -= graph->vertices[u]->force * sin * temperature;

      energy1 += graph->vertices[u]->force * 2;

      usleep(10000);
    }
  }
}

void MultiLevel::initialPlacement() {
  char *digit = new char[64];
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < graph->numVertices; ++j) {
    sprintf(digit, "%d", j);
    graph->vertices[j]->posX = 0;
    graph->vertices[j]->posY = 0;
    graph->vertices[j]->posZ = -100;
    graph->vertices[j]->setText(digit);
    graph->vertices[j]->setColour(((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)));
  }
  graph->vertices[0]->posX = 0;
  graph->vertices[0]->posY = 0;
  graph->vertices[0]->posZ = 0;
  delete(digit);
}

void MultiLevel::placement() {
//  fprintf(stderr, "PLACEMENT Edge = %d\n",edgeIndex);
  //sleep(1);
  double radius = 10 / numVerticesF;
  int v = graph->edgeList[edgeIndex][0];
  graph->vertices[v]->level = level;

  int a = graph->edgeList[edgeIndex][1];
  graph->vertices[a]->level = level;

  graph->vertices[v]->posZ = 0;
  graph->vertices[a]->posZ = 0;

  visitedVertices[v] = 1;
  visitedVertices[a] = 1;

  graph->vertices[a]->posX = graph->vertices[v]->posX +
      cos((2 * M_PI * edgeIndex) / numVerticesF) * radius;

  graph->vertices[a]->posY = graph->vertices[v]->posY +
      sin((2 * M_PI * edgeIndex) / numVerticesF) * radius;

  //v vertex
  if (graph->vertices[v]->posX > max_x)
    max_x = graph->vertices[v]->posX;
  if (graph->vertices[v]->posX < min_x)
    min_x = graph->vertices[v]->posX;
  if (graph->vertices[v]->posY > max_y)
    max_y = graph->vertices[v]->posY;
  if (graph->vertices[v]->posY < min_y)
    min_y = graph->vertices[v]->posY;

  //a vertex
  if (graph->vertices[a]->posX > max_x)
    max_x = graph->vertices[a]->posX;
  if (graph->vertices[a]->posX < min_x)
    min_x = graph->vertices[a]->posX;
  if (graph->vertices[a]->posY > max_y)
    max_y = graph->vertices[a]->posY;
  if (graph->vertices[a]->posY < min_y)
    min_y = graph->vertices[a]->posY;
  // Ugly af but idc it's the same speed
  diagonal = abs(max_x - min_x) + abs(max_y - min_y);

  if (edgeIndex + 1 < (graph->numEdges)) {
    //fprintf(stderr, "%d - %d,%d\n", edgeIndex, v, a);
    if (graph->edgeList[edgeIndex + 1][0] == v) {
      edgeIndex++;
      placement();
    } else {
      level++;
      edgeIndex++;
    }
  } else
    edgeIndex++;
}


