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

  adjacencyMatrix = new int *[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    adjacencyMatrix[i] = new int[numVertices];
    for (int j = 0; j < numVertices; ++j) {
      adjacencyMatrix[i][j] = edgeList[i][j];
    }
  }

  for (int j = 0; j < numVertices; ++j) {
    vertices.push_back(new Vertex(0, 0, 0));
    vertices[j]->setColour(0, 0, 0);
  }

  for (int i = 0; i < numVertices; ++i) {
    for (int j = i; j < numVertices; ++j) {
      if(j == i) continue;
      if (adjacencyMatrix[i][j] == 1) {
        vertices[i]->attachPoint(vertices[j]);
        vertices[i]->degree++;
        vertices[j]->degree++;
      }
    }
  }

  int *temp = new int[2];
  edgeList.clear();
  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < i; ++j) {
      if (adjacencyMatrix[i][j] == 1) {
        temp[0] = j;
        temp[1] = i;
        edgeList.push_back(temp);
        temp = new int[2];
      }
    }
  }
  numEdges = edgeList.size();

  for (int i = 0; i < edgeList.size(); ++i) {
    fprintf(stderr, "%d,%d\n", edgeList[i][0], edgeList[i][1]);
  }
}
AdjacencyGraph::~AdjacencyGraph() {
  fprintf(stderr, "Deleting AdjacencyGraph\n");

}
