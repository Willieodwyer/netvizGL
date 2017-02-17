//
// Created by werl on 15/01/17.
//

#ifndef NETVIZGL_COLOURNODECOMMAND_H
#define NETVIZGL_COLOURNODECOMMAND_H

#include <algorithm>
#include "../GLWindow.h"
#include "Command.h"

class ColourNode : public Command {
 private:
  GLWindow *window;
 public:
  ColourNode(GLWindow *pWindow) {
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
        pointerOver[i]->setColour(Widget::Ins()->redColour,
                                  Widget::Ins()->greenColour,
                                  Widget::Ins()->blueColour);
      }
    }
  };
};

#endif //NETVIZGL_COLOURNODECOMMAND_H
