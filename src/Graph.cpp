//
// Created by werl on 25/10/16.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "../inc/Graph.h"

Graph::Graph(const char *filePath) {

  numVertices = 0;

  vector<int *> edgeList;

  string inString;
  ifstream inFile;

  inFile.open(filePath);
  if (inFile.is_open()) {
    //fprintf(stderr,"Open %s \n", filePath);
  } else {
    fprintf(stderr, "Failed to open %s \n", filePath);
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

  std::srand(std::time(0));
  for (int j = 0; j < numVertices; ++j) {
    points.push_back(new Point(rand() % 20, rand() % 20, rand() % 20, j));
    points[j]->setColour(((double) rand() / (RAND_MAX)),
                         ((double) rand() / (RAND_MAX)),
                         ((double) rand() / (RAND_MAX)));
  }

  for (int k = 0; k < edgeList.size(); ++k) {
    points[edgeList[k][0]]->attachPoint(points[edgeList[k][1]]);
  }

}

int *Graph::split(string str) {
  int *retNums = new int[2];
  stringstream ss(str);
  string tok;

  int c = 0;
  while (getline(ss, tok, ' ')) {
    retNums[c++] = atoi(tok.c_str());
  }

  return retNums;
}

void Graph::draw() {
  for (int i = 0; i < numVertices; ++i) {
    points[i]->draw();
  }
}
