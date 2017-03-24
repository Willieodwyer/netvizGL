//
// Created by william on 13/03/17.
//

#include <iostream>
#include <algorithm>
#include "../../inc/Centrality/Betweenness.h"
void Betweenness::calcApply(Graph *g) {
  vals = new int[g->numVertices];
  for (int i = 0; i < g->numVertices; ++i) {
    vals[i] = 0;
  }
  buildTree(g);
  BFS(g, 6, 7);
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
  vector<int> path;
  queue.push_back(v);

  int i = v;
  while (!found) {
    for (int j = 0; j < tree[i].size(); ++j) {
      int x = tree[i][j];
      if (visited[tree[i][j]] != 1 && std::find(queue.begin(), queue.end(), x) == queue.end()) {
        queue.push_back(tree[i][j]);
      }
      cerr << "check: " << i << "," << tree[i][j] << endl;
      if (tree[i][j] == u) {
        found = true;
        break;
      }
    }

    if (visited[queue[queueIndex]] != 1 && !found) {
      cerr << "move to:" << queue[queueIndex] << endl;
      visited[queue[queueIndex]] = 1;
      i = queue[queueIndex];
    }
    queueIndex++;
  }
  cerr << "found" << endl;
  for (int i = 0; i < queue.size(); ++i) {
    cerr << queue[i] << " ";
  }
  cerr << endl;
};

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
    cerr << i << " - ";
    for (int j = 0; j < tree[i].size(); ++j) {
      cerr << tree[i][j] << " ";
    }
    cerr << endl;
  }

}

