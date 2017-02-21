//
// Created by william on 24/01/17.
//

#ifndef NETVIZGL_TEXTNODECOMMAND_H
#define NETVIZGL_TEXTNODECOMMAND_H

#include <algorithm>
#include "../GLWindow.h"
#include "Command.h"

class TextNode : public Command {
 private:
  GLWindow *window;
 public:
  TextNode(GLWindow *pWindow)
      : window(pWindow) {

  }

  void execute() {
    vector<Vertex *> pointerOver;
    vector<double> depthValues;

    if (window->graph) {
      for (int i = 0; i < window->graph->numVertices; ++i) {
        if (window->graph->vertices[i]->isPointerOver(window->mouseX, window->mouseY,
                                                      window->windowWidth, window->windowHeight)) {
          pointerOver.push_back(window->graph->vertices[i]);
        }
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
        pointerOver[i]->setText(Widget::Ins()->textNodeText);
      }
    }
  }

};

#endif //NETVIZGL_TEXTNODECOMMAND_H
