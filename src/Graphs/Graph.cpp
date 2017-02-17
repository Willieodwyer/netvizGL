//
// Created by werl on 25/10/16.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include "../../inc/Graphs/Graph.h"

Graph::Graph(char *filePath) {
  numVertices = 0;
}

int *Graph::split(string str) {
  std::istringstream buf(str);
  std::istream_iterator<std::string> beg(buf), end;

  std::vector<std::string> tokens(beg, end);

  int *ret = new int[tokens.size()];
  for (int i = 0; i < tokens.size(); ++i)
    ret[i] = atoi(tokens[i].c_str());

  return ret;
}

unsigned int Graph::hash3(unsigned int h1, unsigned int h2, unsigned int h3) {
  return ((h1 * 2654435789U) + h2) * 2654435789U + h3;
}

Graph::~Graph() {
  fprintf(stderr, "Deleting Graph\n");
  vertices.clear();
  adjacencyMatrix.clear();
}

