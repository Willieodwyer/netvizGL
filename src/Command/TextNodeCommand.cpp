//
// Created by william on 24/01/17.
//

#include <algorithm>
#include "../../inc/Command/TextNodeCommand.h"

void TextNodeCommand::execute() {
  vector<Vertex *> pointerOver;
  vector<double> depthValues;

  if(window->graph) {
    for (int i = 0; i < window->graph->numVertices; ++i) {
      if (window->graph->vertices[i]->isPointerOver(window->mouseX, window->mouseY)) {
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
TextNodeCommand::TextNodeCommand(GLWindow *pWindow)
    : window(pWindow) {

}
