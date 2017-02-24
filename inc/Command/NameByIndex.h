//
// Created by william on 24/02/17.
//

#ifndef NETVIZGL_NAMEBYINDEX_H
#define NETVIZGL_NAMEBYINDEX_H

#include "Command.h"
#include "../GLWindow.h"
class NameByIndex : public Command {
 private:
  GLWindow *window;
 public:
  NameByIndex(GLWindow *window) : window(window) {
  }
  void execute() override {
    static bool toggle = false;
    char *digit = new char[64];    for (int j = 0; j < window->graph->numVertices; ++j) {
      sprintf(digit, "%d", j);
      if (!toggle)
        window->graph->vertices[j]->setText(digit);
      else {
        window->graph->vertices[j]->setText("");
      }
    }
    toggle = !toggle;
  }
};

#endif //NETVIZGL_NAMEBYINDEX_H
