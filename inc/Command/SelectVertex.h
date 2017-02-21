//
// Created by william on 21/02/17.
//

#ifndef NETVIZGL_SELECTVERTEX_H
#define NETVIZGL_SELECTVERTEX_H

#include <algorithm>
#include "Command.h"
#include "../GLWindow.h"

class SelectVertex : public Command{
 private:
  GLWindow *window;
 public:
  SelectVertex(GLWindow *pWindow) {
    this->window = pWindow;
  }
  void execute() override {
    vector<Vertex *> pointerOver;
    vector<double> depthValues;

    if (window->graph) {
      for (int i = 0; i < window->graph->numVertices; ++i) {
        Widget::updateColour();
        if (window->graph->vertices[i]->isPointerOver(window->mouseX,
                                                      window->mouseY,
                                                      window->windowWidth,
                                                      window->windowHeight)) {
          pointerOver.push_back(window->graph->vertices[i]);

        }
        if(window->graph->vertices[i]->selected){
          window->graph->vertices[i]->selected = false;
        }
        window->graph->vertices[i]->nodeNumber = i;
      }
    }

    if (pointerOver.size() == 0) {
      return;
    }

    for (int i = 0; i < pointerOver.size(); i++) {
      depthValues.push_back(pointerOver[i]->getDepth());
    }

    double closest = *std::min_element(depthValues.begin(), depthValues.end());

    double *cols = new double[3];
    for (int i = 0; i < pointerOver.size(); i++) {
      if (closest == depthValues[i]) {
        pointerOver[i]->selected = true;
        window->selectedNodeNumber = pointerOver[i]->nodeNumber;
        pointerOver[i]->getColour(cols);
        pointerOver[i]->getColour(cols);

        GLWindow::Ins()->selectedNode = pointerOver[i];

        Widget::Ins()->redColour = cols[0];
        Widget::Ins()->greenColour = cols[1];
        Widget::Ins()->blueColour = cols[2];
        Widget::Ins()->textNodeText = pointerOver[i]->text;
        Widget::updateNodeDetails();
      }
    }
  };
};

#endif //NETVIZGL_SELECTVERTEX_H
