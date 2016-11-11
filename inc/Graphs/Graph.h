//
// Created by werl on 25/10/16.
//
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <string>
#include "../Vertex.h"

#ifndef NETVIZGL_GRAPH_H
#define NETVIZGL_GRAPH_H
using namespace std;

class Graph {
 public:
  Graph(const char *filePath);

  vector<Vertex *> vertices;
  int numVertices;
  int **edges;

  virtual void draw() = 0;
  virtual void update() = 0;

  int *split(string x);
  unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3);

 private:
  virtual void read(const char *filePath) = 0;
};

#endif //NETVIZGL_GRAPHREADER_H
