//
// Created by william on 30/01/17.
//

#include <zconf.h>
#include <sys/time.h>
#include "../../inc/Algorithms/MultiLevel.h"

MultiLevel::MultiLevel(Graph *g) : Algorithm(g) {
  completedVertices = 0; //Number of completed Vertices
  edgeIndex = 0; // First edgeIndex or random edgeIndex
  level = 1; //Level of vertices
  numVerticesF = (double) graph->numVertices;
  baseEdge = 0, connectedEdge = 0; // Index of the vertex for the base and connected edge
  population = 2;
  iterations = 0;
  fin = false;
  initialPlacement();
  k = 1;
  cooling = 0.99;
  temperature = 0.1;
}

void MultiLevel::apply() {
  if (!fin) {
    if (edgeIndex < graph->numEdges)
      placement(edgeIndex, edgeIndex++);
    calcApplyForces();

//    for (int i = 0; i < graph->numVertices; i++) {
//      if (graph->vertices[i]->level == level) { // If the level of the visited vertex is equal to this level
//        for (int j = 0; j < graph->numVertices; j++) {
//          baseEdge = graph->edgeList[edgeIndex][0];
//          connectedEdge = graph->edgeList[edgeIndex][1];
//          edgeIndex++;
//
//          if ((graph->vertices[connectedEdge]->level == 0)) {// If i havn't visited this vertex yet
//            graph->vertices[connectedEdge]->level = level + 1;
//            graph->vertices[connectedEdge]->posX = graph->vertices[i]->posX + (cos(1));
//            graph->vertices[connectedEdge]->posX = graph->vertices[i]->posY + (sin(1));
//            visitedVertices.push_back(graph->vertices[connectedEdge]);
//            edgeIndex++;
//            completedVertices++;
//          } else if (graph->vertices[baseEdge]->level == 0) {
//            graph->vertices[baseEdge]->level = level + 1;
//            graph->vertices[baseEdge]->posX = graph->vertices[i]->posX + (cos(1));
//            graph->vertices[baseEdge]->posX = graph->vertices[i]->posY + (sin(1));
//            visitedVertices.push_back(graph->vertices[baseEdge]);
//            edgeIndex++;
//            completedVertices++;
//          }
//        }
//      }

    level++;
    if (completedVertices == numVerticesF)
      fin = true;
    iterations++;
  }
}

void MultiLevel::calcApplyForces() {
  double rFactor = sqrt(numVerticesF);
  double aFactor = rFactor * 5;

//  for (int j = 0; j < numVerticesF; j++) {
//    int v1 = graph->edgeList[j][0]; // List of the EDge list that you have
//    int v2 = graph->edgeList[j][1];
//
////    if (visitedVertices[v1] && visitedVertices[v2]) { //If it has been visited
//      double rep = 0;
//      double att = 0;
//      force = 0;
//      double dis = abs(graph->vertices[v1]->posX - graph->vertices[v2]->posX)
//          + abs(graph->vertices[v1]->posY - graph->vertices[v2]->posY);
//
//      if (dis < 0.00000000002) dis = 0.00000000002;
//
//      double cos = ((graph->vertices[v2]->posX - graph->vertices[v1]->posX) / dis);
//      double sin = ((graph->vertices[v2]->posX - graph->vertices[v1]->posY) / dis);
//
////      rep = ((k * k) / -dis);  //Takes care of the distances making sure they're not small
////      att = dis * dis / k;
//
//      force = rep + att;
//      force = 2;
//      energy1 += force * 2;
//
//      double x_t = cos * force;
//      double y_t = sin * force;
//
//      graph->vertices[v1]->posX += x_t;
//      graph->vertices[v1]->posY += y_t;
//
//      graph->vertices[v2]->posX -= x_t;
//      graph->vertices[v2]->posY -= y_t;
////    }
//  }
}
void MultiLevel::initialPlacement() {
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < graph->numVertices; ++j) {
    graph->vertices[j]->posX = 0;
    graph->vertices[j]->posY = 0;
    graph->vertices[j]->posZ = 0;
    graph->vertices[j]->setColour(((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)));
  }
}

void MultiLevel::placement(int p, int j) {
  double radius = 10 / numVerticesF;
  int v = graph->edgeList[p][0];
  for (int i = 0; i < graph->numEdges; ++i) {
    int a = graph->edgeList[p][1];

    graph->vertices[a]->posX = graph->vertices[v]->posX +
        cos((2 * M_PI * p) / numVerticesF) * radius;
    graph->vertices[a]->posY = graph->vertices[v]->posY +
        sin((2 * M_PI * p) / numVerticesF) * radius;
  }
}

