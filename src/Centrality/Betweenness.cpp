//
// Created by william on 13/03/17.
//

#include "../../inc/Centrality/Betweenness.h"
void Betweenness::calcApply(Graph *g) {
  int *vals = new int[g->numVertices];

  for (int i = 0; i < g->numVertices; ++i) {
    for (int j = 0; j < g->numVertices; ++j) {
      findDist(i, j, g);
    }
  }
}

int Betweenness::findDist(int v, int u, Graph *g) {
  for (int i = 0; i < g->edgeList.size(); ++i) {

  }
}

