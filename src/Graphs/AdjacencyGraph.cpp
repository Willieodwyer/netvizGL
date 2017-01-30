//
// Created by werl on 11/11/16.
//

#include <sys/time.h>
#include <cstdlib>
#include <zconf.h>
#include <fstream>
#include "../../inc/Graphs/AdjacencyGraph.h"
AdjacencyGraph::AdjacencyGraph(char *filePath)
    : Graph(filePath) {
  read(filePath);
}

void AdjacencyGraph::draw() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->drawPoints();
  }
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->drawText();
  }
}

void AdjacencyGraph::update() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->update();
  }
}

void AdjacencyGraph::read(char *filePath) {
  vector<int *> edgeList;

  string inString;
  ifstream inFile;

  inFile.open(filePath);
  if (inFile.is_open()) {
    fprintf(stderr, "Open %s \n", filePath);
  } else {
    fprintf(stderr, "Failed to open %s \n", filePath);
    exit(0);
  }

  while (!inFile.eof()) {
    getline(inFile, inString);
    if (inString.size() > 1)
      edgeList.push_back(split(inString));
  }
  inFile.close();

  numVertices = (int) edgeList.size();

  fprintf(stdout, "Vertices - %d\n", numVertices);

  edges = new int *[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    edges[i] = new int[numVertices];
    for (int j = 0; j < numVertices; ++j) {
      edges[i][j] = edgeList[i][j];
    }
  }

  struct timeval time;
  gettimeofday(&time, NULL);
  srand(hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < numVertices; ++j) {
    vertices.push_back(new Vertex(((double) rand() / RAND_MAX) * numVertices - numVertices / 2,
                                  ((double) rand() / RAND_MAX) * numVertices - numVertices / 2,
                                  0));
    vertices[j]->setColour(((double) rand() / (RAND_MAX)),
                           ((double) rand() / (RAND_MAX)),
                           ((double) rand() / (RAND_MAX)));
  }

  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < numVertices; ++j) {
      if (vertices[i]->posX == vertices[j]->posX && i != j
          && vertices[i]->posY == vertices[j]->posY)
        fprintf(stderr, "Warning: duplicate positions generated @ %d\n", i);
    }
  }

  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < numVertices; ++j) {
      if (edges[i][j] == 1)
        vertices[i]->attachPoint(vertices[j]);
    }
  }

}
