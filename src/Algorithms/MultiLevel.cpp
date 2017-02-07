//
// Created by william on 30/01/17.
//

#include "../../inc/Algorithms/MultiLevel.h"

MultiLevel::MultiLevel(Graph *g) : Algorithm(g) {
  completedVertices = 0; //Number of completed Vertices
  edgeIndex = 0; // First edgeIndex or random edgeIndex
  level = 1; //Level of vertices
  numVerticesF = (double) graph->numVertices;
  baseEdge = 0, connectedEdge = 0; // Index of the vertex for the base and connected edge

  iterations = 0;
  fin = false;

  force_x = new double[graph->numVertices];
  force_y = new double[graph->numVertices];

  baseEdge = graph->edgeList[edgeIndex][0];
  connectedEdge = graph->edgeList[edgeIndex][1];
  seenLinks.push_back(graph->edgeList[edgeIndex]);
  edgeIndex++;

  visitedVertices.push_back(graph->vertices[baseEdge]); //visited nodes
  visitedVertices[completedVertices]->level = level;
  graph->vertices[baseEdge]->posX = 0;
  graph->vertices[baseEdge]->posY = 0;
  completedVertices++;

  visitedVertices.push_back(graph->vertices[connectedEdge]); //visited nodes
  visitedVertices[completedVertices]->level = level; //visited nodes
  graph->vertices[connectedEdge]->posX = cos((double) 1.0) * 0.025;
  graph->vertices[connectedEdge]->posY = sin((double) 1.0) * 0.025;
  completedVertices++;
}

void MultiLevel::apply() {
  if (!fin) {
    calcApplyForces();

    if (completedVertices == numVerticesF) {
      fin = true;
    }

    for (int i = 0; i < graph->numVertices; i++) {
      if (graph->vertices[i]->level == level) { // If the level of the visited vertex is equal to this level
        for (int j = 0; j < graph->numVertices; j++) {
          baseEdge = graph->edgeList[edgeIndex][0];
          connectedEdge = graph->edgeList[edgeIndex][1];
          edgeIndex++;

          if ((graph->vertices[connectedEdge]->level == 0)) {// If i havn't visited this vertex yet
            graph->vertices[connectedEdge]->level = level + 1;
            graph->vertices[connectedEdge]->posX = graph->vertices[i]->posX + (cos(1));
            graph->vertices[connectedEdge]->posX = graph->vertices[i]->posY + (sin(1));
            visitedVertices.push_back(graph->vertices[connectedEdge]);
            edgeIndex++;
            completedVertices++;
          } else if (graph->vertices[baseEdge]->level == 0) {
            graph->vertices[baseEdge]->level = level + 1;
            graph->vertices[baseEdge]->posX = graph->vertices[i]->posX + (cos(1));
            graph->vertices[baseEdge]->posX = graph->vertices[i]->posY + (sin(1));
            visitedVertices.push_back(graph->vertices[baseEdge]);
            edgeIndex++;
            completedVertices++;
          }
        }
      }

      level++;
    }
    if (completedVertices == numVerticesF)
      fin = true;
    iterations++;
  }
}

void MultiLevel::calcApplyForces() {

  for (int j = 0; j < graph->numVertices; j++) {
    int v1 = graph->edgeList[j][0]; // List of the EDge list that you have
    int v2 = graph->edgeList[j][1];

    if (visitedVertices[v1] && visitedVertices[v2]) { //If it has been visited
      double rep = 0;
      double att = 0;
      force = 0;
      double dis = abs(graph->vertices[v1]->posX - graph->vertices[v2]->posX)
          + abs(graph->vertices[v1]->posY - graph->vertices[v2]->posY);

      if (dis < 0.00000000002) dis = 0.00000000002;

      double cos = ((graph->vertices[v2]->posX - graph->vertices[v1]->posX) / dis);
      double sin = ((graph->vertices[v2]->posX - graph->vertices[v1]->posY) / dis);

//      rep = ((k * k) / -dis);  //Takes care of the distances making sure they're not small
//      att = dis * dis / k;

      force = rep + att;
      force = 1;
      energy1 += force * 2;

      double x_t = cos * force;
      double y_t = sin * force;

      graph->vertices[v1]->posX += x_t;
      graph->vertices[v1]->posY += y_t;

      graph->vertices[v2]->posX -= x_t;
      graph->vertices[v2]->posY -= y_t;
    }
  }
}

