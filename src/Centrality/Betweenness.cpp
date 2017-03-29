//
// Created by william on 13/03/17.
//

#include <iostream>
#include <algorithm>
#include "../../inc/Centrality/Betweenness.h"
void Betweenness::calcApply(Graph *gr) {
  vals = new double[gr->numVertices];
  for (int i = 0; i < gr->numVertices; ++i) {
    vals[i] = 0;
  }
  buildTree(gr);
  for (int i = 0; i < gr->numVertices; ++i) {
    for (int j = 0; j < gr->numVertices; ++j) {
      if (i == j)
        break;
      BFS(gr, i, j);
    }
  }
  int max = 0, min = 999999999;
  for (int i = 0; i < gr->numVertices; ++i) {
    if (vals[i] > max)
      max = vals[i];
    if (vals[i] < min)
      min = vals[i];
  }

  cerr << min << "," << max << endl;

  double r;
  double g;
  double b;
  double h;
  double x;

  //char *digit = new char[64];
  for (int i = 0; i < gr->numVertices; ++i) {
    x = normalized(vals[i], max, min);

    h = (1 - x) * 240;

    HSVtoRGB(r, g, b, h, 1, 1);

    //sprintf(digit, "%lf", vals[i]);
    gr->vertices[i]->setColour(r, g, b);
//    gr->vertices[i]->setText(digit);
  }
}

void Betweenness::BFS(Graph *g, int v, int u) {
  bool found = false;
  int visited[g->numVertices];
  for (int i = 0; i < g->numVertices; ++i) {
    visited[i] = 0;
  }
  visited[v] = 1;

  int queueIndex = 1;

  vector<int> queue;
  vector<int *> links;
  int *tempLink;
  vector<int> path;
  queue.push_back(v);

  int i = v;
  while (!found) {
    for (int j = 0; j < tree[i].size(); ++j) {
      int x = tree[i][j];
      if (visited[tree[i][j]] != 1 && std::find(queue.begin(), queue.end(), x) == queue.end()) {
        queue.push_back(tree[i][j]);
      }
      //cerr << "check: " << i << "," << tree[i][j] << endl;
      tempLink = new int[2];
      tempLink[0] = i;
      tempLink[1] = tree[i][j];
      links.push_back(tempLink);
      if (tree[i][j] == u) {
        found = true;
        break;
      }
    }

    if (visited[queue[queueIndex]] != 1 && !found) {
      //cerr << "move to:" << queue[queueIndex] << endl;
      visited[queue[queueIndex]] = 1;
      i = queue[queueIndex];
    }
    queueIndex++;
  }
  //cerr << "found" << endl;

  //for (int i = links.size() - 1; i > -1; --i) {
  //cerr << links[i][0] << "," << links[i][1] << endl;
  //}

  int lookFor = u;
  int tempLookFor = 0;
  //cerr << lookFor << endl;
  vals[lookFor]++;
  for (int i = links.size() - 1; i > -1; --i) {
    for (int j = i; j > -1; --j) {
      if (lookFor == links[j][1]) {
//      cerr << links[i][0] << "," << links[i][1] << endl;
        tempLookFor = links[j][0];
      }
    }
    lookFor = tempLookFor;
    //cerr << lookFor << endl;
    vals[lookFor]++;
    if (lookFor == v)
      break;
  }
}

void Betweenness::buildTree(Graph *g) {
  vector<int> localTree;

  for (int i = 0; i < g->adjacencyMatrix.size(); ++i) {
    for (int j = 0; j < g->adjacencyMatrix[0].size(); ++j) {
      if (g->adjacencyMatrix[i][j] == 1)
        localTree.push_back(j);
    }
    tree.push_back(localTree);
    localTree.clear();
  }

  for (int i = 0; i < tree.size(); ++i) {
    //cerr << i << " - ";
    for (int j = 0; j < tree[i].size(); ++j) {
      //cerr << tree[i][j] << " ";
    }
    //cerr << endl;
  }

}

