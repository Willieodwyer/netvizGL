//
// Created by werl on 11/11/16.
//

#include <sys/time.h>
#include <cstdlib>
#include <zconf.h>
#include <fstream>
#include "../../inc/Graphs/EdgeGraph.h"
EdgeGraph::EdgeGraph(char *filePath)
    : Graph(filePath) {
  read(filePath);
}

void EdgeGraph::draw() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->drawPoints();
  }
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->drawText();
  }
}

void EdgeGraph::update() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->update();
  }
}

void EdgeGraph::read(char *filePath) {
  vector<int *> edgeList;

  string inString;
  ifstream inFile;

  inFile.open(filePath);
  if (inFile.is_open()) {
    fprintf(stdout, "\nOpened: %s \n", filePath);
  } else {
    fprintf(stderr, "\nFailed to open %s \n", filePath);
    exit(0);
  }

  while (!inFile.eof()) {
    getline(inFile, inString);
    if (inString.size() > 1)
      edgeList.push_back(split(inString));
  }
  inFile.close();

  for (int i = 0; i < edgeList.size(); ++i) {
    if (edgeList[i][0] > numVertices) {
      numVertices = edgeList[i][0];
    }
    if (edgeList[i][1] > numVertices) {
      numVertices = edgeList[i][1];
    }
  }

  numVertices++;

  edges = new int *[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    edges[i] = new int[numVertices];
    for (int j = 0; j < numVertices; ++j) {
      edges[i][j] = 0;
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

  for (int k = 0; k < edgeList.size(); ++k) {
    vertices[edgeList[k][0]]->attachPoint(vertices[edgeList[k][1]]);
    edges[edgeList[k][0]][edgeList[k][1]] = 1;
    edges[edgeList[k][1]][edgeList[k][0]] = 1;
  }
}

////TODO this
bool EdgeGraph::validate(char *filePath) {

}