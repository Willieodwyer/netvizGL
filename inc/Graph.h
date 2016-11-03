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
  Graph(const char *filePath);
  void draw();

  vector<Vertex *> vertices;
  int **edges;

  void update();

 private:

  int * split(string x);

};

#endif //NETVIZGL_GRAPHREADER_H
