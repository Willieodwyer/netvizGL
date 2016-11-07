//
// Created by werl on 25/10/16.
//

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>
#include <zconf.h>
#include <iterator>
#include <iostream>
#include "../inc/Graph.h"

Graph::Graph(const char *filePath, const char *type) {
  numVertices = 0;

  if (strcmp("edge", type) == 0) {
    readEdgeList(filePath);
  }
  if (strcmp("adj", type) == 0) {
    readAdjacencyList(filePath);
  }

}

void Graph::readAdjacencyList(const char *filePath) {
  vector<int *> edgeList;

  string inString;
  ifstream inFile;

  inFile.open(filePath);
  if (inFile.is_open()) {
    //fprintf(stderr,"Open %s \n", filePath);
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

  fprintf(stdout, "Vertices - %d\n" ,numVertices);

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
      if(edges[i][j] == 1)
        vertices[i]->attachPoint(vertices[j]);
    }
  }

}

void Graph::readEdgeList(const char *filePath) {
  vector<int *> edgeList;

  string inString;
  ifstream inFile;

  inFile.open(filePath);
  if (inFile.is_open()) {
    //fprintf(stderr,"Open %s \n", filePath);
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

int *Graph::split(string str) {
  std::istringstream buf(str);
  std::istream_iterator<std::string> beg(buf), end;

  std::vector<std::string> tokens(beg, end); // done!

//  for (int i = 0; i < tokens.size(); ++i)
//    std::cout << tokens[i] << " ";

  int *ret = new int[tokens.size()];
  for (int i = 0; i < tokens.size(); ++i)
    ret[i] = atoi(tokens[i].c_str());

  //cout << endl;

  return ret;
}

void Graph::draw() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->draw();
  }
}
void Graph::update() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->update();
  }
}
unsigned int Graph::hash3(unsigned int h1, unsigned int h2, unsigned int h3) {
  return ((h1 * 2654435789U) + h2) * 2654435789U + h3;
}
