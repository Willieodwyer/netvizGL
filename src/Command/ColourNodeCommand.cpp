//
// Created by werl on 15/01/17.
//

#include <algorithm>
#include "../../inc/Command/ColourNodeCommand.h"
ColourNodeCommand::ColourNodeCommand(GLWindow *pWindow) {
  this->window = pWindow;
}
void ColourNodeCommand::execute() {
  vector<Vertex *> pointerOver;
  vector<double> depthValues;

  for (int i = 0; i < window->graph->numVertices; ++i) {
    Widget::updateColour();
    if (window->graph->vertices[i]->isPointerOver(window->mouseX, window->mouseY)) {
      pointerOver.push_back(window->graph->vertices[i]);
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
      pointerOver[i]->setColour(Widget::Instance()->redColour,
                                Widget::Instance()->greenColour,
                                Widget::Instance()->blueColour);
    }
  }
}
