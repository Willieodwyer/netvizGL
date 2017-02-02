//
// Created by william on 30/01/17.
//

#include "../../inc/Algorithms/MultiLevel.h"

MultiLevel::MultiLevel(Graph *g) : Algorithm(g) {
  lists = new int *[graph->numVertices];
  for (int i = 0; i < graph->numVertices; ++i) {
    lists[i] = new int[graph->numVertices];
    for (int j = 0; j < graph->numVertices; ++j) {
      lists[i][j] = 0;
    }
  }
  degree_met = new int[graph->numVertices];

  completedVertices = 0;
  linkIndex = 0; // First linkIndex or random linkIndex
  level = 1;
  numVerticesF = (double) graph->numVertices;
  display = 10.0 / numVerticesF;
  tolerance = 0.1;
  base = 0, connected = 0;
  ini = new int[2];

  iterations = 0;
  di = 0.5;
  ti = 0.1;
  ti_lev = ti;
  ti_rate = 0.9;
  k_rate = 0.99;
  rnd = round(sqrt(numVerticesF));

  fin = false;

  force_x = new double[graph->numVertices];
  force_y = new double[graph->numVertices];

  base = graph->edgeList[linkIndex][0];
  connected = graph->edgeList[linkIndex][1];

  ini[0] = base;
  ini[1] = connected;

  seen_links.push_back(ini);

  completedVertices++;
  visitedVertices.push_back(graph->vertices[base]); //visited nodes
  graph->vertices[base]->posX = 0;
  graph->vertices[base]->posY = 0;
  degree_met[base]--;

  completedVertices++;
  visitedVertices.push_back(graph->vertices[connected]); //visited nodes
  graph->vertices[connected]->posX = cos((double) 1.0) * 0.025;
  graph->vertices[connected]->posY = sin((double) 1.0) * 0.025;
  degree_met[connected]--;

  k = 0.5 / completedVertices;
}

void MultiLevel::apply() {
  if (!fin) {
    k = di / ((completedVertices));
    ti = ti * ti_rate;

    energy1 = 0;
    calculateForces((int) graph->numEdges, linkIndex);

    // Add up the forces
    for (int i = 0; i < visitedVertices.size(); i++) {
      if (visitedVertices[i]->level != 0) {
        graph->vertices[i]->posX =
            graph->vertices[i]->posX + (force_x[i] * ti);
        graph->vertices[i]->posY =
            graph->vertices[i]->posY + (force_y[i] * ti);
      }
    }

    if ((abs(energy1 - energy0) < tolerance * display && completedVertices == numVerticesF)) {
      fin = true;
      int_pr = 0;
    }

    if (abs(energy1 - energy0) < tolerance * display  /*(iterations % rnd)==0*/) {
      di = di * k_rate; // mesh

      for (int i = 0; i < visitedVertices.size(); i++) {
        if (visitedVertices[i]->level == level) { //level of the nodes
          double s = 0;
          double chunk = (M_PI * 2.0) / (double) degree_met[i];

          for (int j = 0; j < graph->edgeList.size(); j++) {
            base = graph->edgeList[linkIndex][0];
            connected = graph->edgeList[linkIndex][1];
            if ((base == i && visitedVertices[connected]->level == 0)) {

              visitedVertices[connected]->level = level + 1;

              graph->vertices[connected]->posX = graph->vertices[i]->posX + (cos(chunk * s) * display);
              graph->vertices[connected]->posX = graph->vertices[i]->posY + (sin(chunk * s) * display);
              s += 1;
              fprintf(stderr,"Err\n");
              completedVertices++;
              linkIndex++;
              degree_met[connected]--;
            } else if (connected == i && visitedVertices[base] == 0) {

              visitedVertices[base]->level = level + 1;

              graph->vertices[base]->posX = graph->vertices[i]->posX + (cos(chunk * s) * display);
              graph->vertices[base]->posY = graph->vertices[i]->posY + (sin(chunk * s) * display);
              s += 1;
              completedVertices++;
              degree_met[base]--;
            }
          }
        }
      }

      level++;
      ti = ti_lev;
      int_pr = 0;
    }
    int_pr++;
    energy0 = energy1;

    if (completedVertices == numVerticesF)
      fin = true;

    iterations++;
  }
}

void MultiLevel::calculateForces(int numV, int s) {
  ch1 = sqrt((double) graph->numVertices); //Makes sure it's not too long in either axis
  ch2 = ch1 * 5;

  for (int j = s; j < numV; j++) {
    int v1 = graph->edgeList[j][0]; // List of the EDge list that you have
    int v2 = graph->edgeList[j][1];

    if (visitedVertices[v1] && visitedVertices[v2]) {
      double rep = 0;
      double att = 0;
      force = 0;
      com++;
      double dis = abs(graph->vertices[v1]->posX - graph->vertices[v2]->posX)
          + abs(graph->vertices[v1]->posY - graph->vertices[v2]->posY);

      if (dis < 0.00000000002) dis = 0.00000000002;

      double cos = ((graph->vertices[v2]->posX - graph->vertices[v1]->posX) / dis);
      double sin = ((graph->vertices[v2]->posX - graph->vertices[v1]->posY) / dis);

      rep = ((k * k) / -dis);  //Takes care of the distances making sure they're not small
      att = dis * dis / k;

      force = rep + att;

      if (force > 0 && force > hypotenuse / ch1)
        force = hypotenuse / ch1;
      if (force < 0 && abs(force) > hypotenuse / ch2)
        force = -hypotenuse / ch2;

      energy1 += force * 2;

      double x_t = cos * force;
      double y_t = sin * force;

      force_x[v1] += x_t;
      force_y[v1] += y_t;

      force_x[v2] -= x_t;
      force_y[v2] -= y_t;
    }
  }
}

