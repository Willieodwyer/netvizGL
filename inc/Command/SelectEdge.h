//
// Created by william on 24/02/17.
//

#ifndef NETVIZGL_SELECTEDGE_H
#define NETVIZGL_SELECTEDGE_H

#include <algorithm>
#include <iostream>
#include "Command.h"
#include "../GLWindow.h"
class SelectEdge : public Command {
 private:
  GLWindow *window;
  Vertex *secondVertex = NULL;
  bool edgeBetween = false;
 public:
  SelectEdge(GLWindow *pWindow) {
    this->window = pWindow;
  }
  void execute() override {
    vector<Vertex *> pointerOver;
    vector<double> depthValues;

    if (window->graph) {
      for (int i = 0; i < window->graph->numVertices; ++i) {
        if (window->graph->vertices[i]->isPointerOver(window->mouseX,
                                                      window->mouseY,
                                                      window->windowWidth,
                                                      window->windowHeight)) {
          pointerOver.push_back(window->graph->vertices[i]);

        }
        if (window->graph->vertices[i]->selected && i != window->selectedVertexNumber) {
          window->graph->vertices[i]->selected = false;
        }
        window->graph->vertices[i]->vertexNumber = i;
      }
    }

    if (pointerOver.size() == 0) {
      return;
    }

    for (int i = 0; i < pointerOver.size(); i++) {
      depthValues.push_back(pointerOver[i]->getDepth());
    }

    double closest = *std::min_element(depthValues.begin(), depthValues.end());

    for (int i = 0; i < pointerOver.size(); i++) {
      if (closest == depthValues[i]) {
        secondVertex = pointerOver[i];
      }
    }

    for (int i = 0; i < window->graph->numEdges; ++i) {
      edgeBetween = (window->graph->edgeList[i][0] == window->selectedVertexNumber
          && window->graph->edgeList[i][1] == secondVertex->vertexNumber)
          || (window->graph->edgeList[i][1] == window->selectedVertexNumber
              && window->graph->edgeList[i][0] == secondVertex->vertexNumber);
      if (edgeBetween) {
        window->selectedEdgeIndex = i;
        secondVertex->selected = true;
        break;
      }
    }

//    if (edgeBetween)
//      cerr << "EDGE BETWEEN: " << window->graph->edgeList[window->selectedEdgeIndex][0] << ","
//           << window->graph->edgeList[window->selectedEdgeIndex][1] << endl;

    if (edgeBetween) {
      int u = window->graph->edgeList[window->selectedEdgeIndex][0];
      int v = window->graph->edgeList[window->selectedEdgeIndex][1];

      for (int i = 0; i < window->graph->vertices[u]->attachedPoints.size(); ++i) {
        if (window->graph->vertices[u]->attachedPoints[i]->vertexNumber == v) {
          Widget::Ins()->textEdgeText = window->graph->vertices[u]->edges[i]->text;
          Widget::Ins()->edgeRedColour = window->graph->vertices[u]->edges[i]->colours[0];
          Widget::Ins()->edgeGreenColour = window->graph->vertices[u]->edges[i]->colours[1];
          Widget::Ins()->edgeBlueColour = window->graph->vertices[u]->edges[i]->colours[2];
        }
      }

      for (int i = 0; i < window->graph->vertices[v]->attachedPoints.size(); ++i) {
        if (window->graph->vertices[v]->attachedPoints[i]->vertexNumber == u) {
          Widget::Ins()->textEdgeText = window->graph->vertices[v]->edges[i]->text;
          Widget::Ins()->edgeRedColour = window->graph->vertices[v]->edges[i]->colours[0];
          Widget::Ins()->edgeGreenColour = window->graph->vertices[v]->edges[i]->colours[1];
          Widget::Ins()->edgeBlueColour = window->graph->vertices[v]->edges[i]->colours[2];
        }
      }

      Widget::updateEdgeDetails();
    }
  }
};

#endif //NETVIZGL_SELECTEDGE_H
