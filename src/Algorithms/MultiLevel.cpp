//
// Created by william on 30/01/17.
//

#include <zconf.h>
#include <sys/time.h>
#include <iostream>
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

  max_x = 0;
  max_y = 0;
  min_x = 0;
  min_y = 0;

  scaleOnce = false;
  done = false;
  t = 0;
  tolerance = 0.1;
  displacement = 100 / numVerticesF;

//  Initiate an adjacent pair of vertices.
//  Initiate population to 2.
//  Initiate k, cooling and temperature.

  initialPlacement();
  k = 0;
  cooling = 0.99;
  temperature = 0.1;
  alpha = 0.5;

  k = sqrt(128 * 72 / (double) graph->numVertices);

}

void MultiLevel::apply() {
  if (!fin) {
    if (edgeIndex < (graph->numEdges)) {
      placement();
    }

//    k = alpha / ((population));


//    while (abs(energy1 - energy0) < tolerance * displacement) {
    while (energy0 > k) {
      energy1 = 0;
      calcApplyForces();
      temperature = temperature * cooling;
      alpha = alpha * cooling;
    }

//    energy0 = energy1;
    energy0 = 10E100;
    temperature = .1;

    if (edgeIndex == graph->numEdges) {
      scaleOnce = true;
      fin = true;
    }

    if (fin)
      fprintf(stderr, "Finished\n");
    t++;
    fprintf(stderr, "level - %d\n", level);
  }
  if (scaleOnce && !done) {
    for (int i = 0; i < graph->numVertices; ++i) {
      graph->vertices[i]->posX = (graph->vertices[i]->posX * (10)) - 25;
      graph->vertices[i]->posY = (graph->vertices[i]->posY * (10)) - 25;
      done = true;
    }
  }
}

void MultiLevel::calcApplyForces() {
  rFactor = sqrt(numVerticesF);
  aFactor = rFactor * 5;

  if (diagonal < 0.1) {
    rFactor = rFactor * (0.1);
    aFactor = aFactor * (0.1);
  }

//  Update cooling.
//  Update k.
//  Update temperature.

  for (int i = 0; i < graph->numEdges; i++) {
    int v = graph->edgeList[i][0]; // List of the EDge list that you have
    int u = graph->edgeList[i][1]; // List of the EDge list that you have


    if (visitedVertices[v] && visitedVertices[u]) {
      std::cerr << "calc forces v:" << v << " u:" << u << std::endl;

      double rep = 0;
      double att = 0;

      double xDist = (graph->vertices[v]->posX - graph->vertices[u]->posX);
      double yDist = (graph->vertices[v]->posY - graph->vertices[u]->posY);
      double d = sqrt((xDist * xDist) + (yDist * yDist));

      if (d < 0.00000000002) d = 0.00000000002;

      double cos = ((graph->vertices[u]->posX - graph->vertices[v]->posX) / d);
      double sin = ((graph->vertices[u]->posY - graph->vertices[v]->posY) / d);

      att = (k * k) / -d;  //Takes care of the distances making sure they're not small
      rep = (d * d) / k;

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

      graph->vertices[u]->posX += graph->vertices[u]->force * -cos * temperature;
      graph->vertices[u]->posY += graph->vertices[u]->force * -sin * temperature;

//      energy1 += graph->vertices[v]->force;
//      energy1 += graph->vertices[u]->force;
      energy0 = graph->vertices[v]->force + graph->vertices[u]->force;

    }
  }
  cerr << endl;

  //usleep(1000000);

}


void MultiLevel::initialPlacement() {
  char *digit = new char[64];
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < graph->numVertices; ++j) {
    sprintf(digit, "%d", j);
    graph->vertices[j]->posX = 1;
    graph->vertices[j]->posY = 1;
    graph->vertices[j]->posZ = -100;
    graph->vertices[j]->setText(digit);
    graph->vertices[j]->setColour(((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)));
  }
  graph->vertices[0]->posX = 0;
  graph->vertices[0]->posY = 0;
  graph->vertices[0]->posZ = 0;
  delete (digit);
}

void MultiLevel::placement() {
  double radius = 10 / numVerticesF;

  int v = graph->edgeList[edgeIndex][0];
  int a = graph->edgeList[edgeIndex][1];

  //calculate J
  double connectedEdges = 1;
  while (edgeIndex + connectedEdges < (graph->numEdges) &&
      graph->edgeList[edgeIndex + connectedEdges][0] == v) {
    connectedEdges++;
  }

  vector<int> connectedNodes;
  for (int l = 0; l < graph->numEdges; ++l) {
    if (graph->edgeList[l][0] == v)
      connectedNodes.push_back(graph->edgeList[l][1]);
  }

  for (int l = 0; l < graph->numEdges; ++l) {
    if (graph->edgeList[l][1] == v)
      connectedNodes.push_back(graph->edgeList[l][0]);
  }

  for (int i = 0; i < connectedEdges; ++i) {
    graph->vertices[v]->level = level;

    a = connectedNodes[i];
    graph->vertices[a]->level = level;

    graph->vertices[v]->posZ = 0;
    graph->vertices[a]->posZ = 0;

    if (visitedVertices[v] != 1) {
      population++;
      visitedVertices[v] = 1;
    }
    if (visitedVertices[a] != 1) {
      population++;
      visitedVertices[a] = 1;
    }

    std::cerr << "placement v:" << v << " u:" << a << std::endl;

    graph->vertices[a]->posX = graph->vertices[v]->posX +
        cos((2 * M_PI * edgeIndex) / connectedNodes.size()) * radius;

    graph->vertices[a]->posY = graph->vertices[v]->posY +
        sin((2 * M_PI * edgeIndex) / connectedNodes.size()) * radius;

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

    edgeIndex++;
    //usleep(1000000);

  }

  level++;
  cerr << endl;
}

void MultiLevel::updateDiagonal() {

}
void MultiLevel::updateCooling() {

}
void MultiLevel::updateK() {

}
void MultiLevel::updateTemperature() {

}


