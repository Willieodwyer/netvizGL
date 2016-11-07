//
// Created by werl on 25/10/16.
//
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <string>
#include "Vertex.h"

#ifndef NETVIZGL_GRAPH_H
#define NETVIZGL_GRAPH_H
using namespace std;

class Graph {
 public:

  int numVertices;
  Graph(const char *filePath, const char *type);
  void draw();

  vector<Vertex *> vertices;
  int **edges;

  void update();

 private:

  int * split(string x);

  unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3);
  void readEdgeList(const char *filePath);
  void readAdjacencyList(const char *filePath);
};

#endif //NETVIZGL_GRAPHREADER_H
