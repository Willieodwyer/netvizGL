//
// Created by william on 02/03/17.
//

#include <zconf.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include "../../inc/Algorithms/MultiForce.h"
#include "../../inc/Graphs/EdgeGraph.h"
#include "../../inc/GLWindow.h"
MultiForce::MultiForce(Graph *g) : Algorithm(g) {
  W = 128;
  L = 72;
  area = W * L;
  k = sqrt(area / (double) graph->numVertices);
  t = graph->numVertices;
  initialPlacement();
  doPlace = true;

  seenVertices.push_back(0);
  for (int i = 0; i < graph->edgeList.size(); ++i) {
    if (graph->edgeList[i][0] == 0) {
      newEdgeList.push_back(graph->edgeList[i]);
      seenVertices.push_back(graph->edgeList[i][1]);
    }
  }

  temp = graph;
  graph = new EdgeGraph(newEdgeList);

  ofstream myfile;
  myfile.open("./LastEditedGraph");
  for (int i = 0; i < newEdgeList.size(); ++i) {
    myfile << newEdgeList[i][0] << " " << newEdgeList[i][1] << endl;
  }
  myfile.close();

  GLWindow::Ins()->graphFilePath = (char *) "./LastEditedGraph";
}

void MultiForce::apply() {
  if (edgeIndex < graph->numEdges) {

    if (doPlace) {
      placement();
//      doPlace = false;
    }

    energy = 1;
    while (energy) {
      cerr << "EN:" << energy << endl;
      energy = 0;

      Vertex *v;
      Vertex *u;

      for (int i = 0; i < seenVertices.size(); ++i) {
        v = graph->vertices[seenVertices[i]];
        v->forceX = 0;
        v->forceY = 0;

        for (int j = 0; j < seenVertices.size(); ++j) {
          if (i == j) continue;

          u = graph->vertices[seenVertices[j]];
          double xDist = (v->posX - u->posX);
          double yDist = (v->posY - u->posY);
          double dist = sqrt((xDist * xDist) + (yDist * yDist));

          if (dist < 0.00000000002) dist = 0.00000000002;

          double repulsion = k * k / dist;
          v->forceX += xDist / dist * repulsion;
          v->forceY += yDist / dist * repulsion;
        }
      }

      for (int i = 0; i < newEdgeList.size(); ++i) {
        v = graph->vertices[newEdgeList[i][0]];
        u = graph->vertices[newEdgeList[i][1]];

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

      for (int i = 0; i < seenVertices.size(); ++i) {
        v = graph->vertices[seenVertices[i]];
        v->posX += v->forceX * 0.000015;
        v->posY += v->forceY * 0.000015;

        cerr << v->forceX * 0.000015 << "," << v->forceY * 0.000015 << endl;
        energy += v->forceX * 0.000015;
        energy += v->forceY * 0.000015;
////    v->velocityX = min(t, max(-t, (v->velocityX + v->forceX)));
////    v->velocityY = min(t, max(-t, (v->velocityY + v->forceY)));
//
//    v->posX += (v->forceX / (abs(v->forceX))) * min(t, max(-t, (v->forceX)));
//    v->posY += (v->forceY / (abs(v->forceY))) * min(t, max(-t, (v->forceY)));

//    v->posX = min(4*W, max(-4*W, v->posX));
//    v->posY = min(4*L, max(-4*L, v->posY));
      }
    }
  }
}

void MultiForce::placement() {
  double radius = 100 / graph->numVertices;

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
    a = connectedNodes[i];

    graph->vertices[v]->posZ = 0;
    graph->vertices[a]->posZ = 0;

    cerr << "placement v:" << v << " u:" << a << endl;

    graph->vertices[a]->posX = graph->vertices[v]->posX +
        cos((2 * M_PI * edgeIndex) / connectedNodes.size()) * radius;

    graph->vertices[a]->posY = graph->vertices[v]->posY +
        sin((2 * M_PI * edgeIndex) / connectedNodes.size()) * radius;

    edgeIndex++;
    usleep(1000000);
  }
  GLWindow::Ins()->algorithm->graph = graph;
  GLWindow::Ins()->graph = graph;
  // << endl;
}

void MultiForce::initialPlacement() {
//char *digit = new char[64];

  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < graph->numVertices; ++j) {
    //sprintf(digit, "%d", j);
    //graph->vertices[j]->setText(digit);
    graph->vertices[j]->posX = ((double) rand()) / RAND_MAX * (W) - W / 2;
    graph->vertices[j]->posY = ((double) rand()) / RAND_MAX * (L) - L / 2;
    graph->vertices[j]->posZ = -9999990;
  }

//  for (int i = 0; i < graph->numVertices; ++i) {
//    for (int j = 0; j < graph->numVertices; ++j) {
//      if (graph->vertices[i]->posX == graph->vertices[j]->posX && i != j
//          && graph->vertices[i]->posY == graph->vertices[j]->posY)
//        fprintf(stderr, "Warning: duplicate positions generated @ %d\n", i);
//    }
//  }
}
