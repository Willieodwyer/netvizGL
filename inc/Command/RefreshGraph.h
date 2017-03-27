//
// Created by william on 15/02/17.
//

#ifndef NETVIZGL_REFRESHGRAPHCOMMAND_H
#define NETVIZGL_REFRESHGRAPHCOMMAND_H

#include "Command.h"
#include "../GLWindow.h"
#include "../Algorithms/MultiForce.h"
#include "../Algorithms/FruchtermanReingold.h"
#include "../Algorithms/SFDAdapter.h"

class RefreshGraph : public Command {
 private:
  GLWindow *window;
 public:
  RefreshGraph(GLWindow *window) : window(window) {}

  void execute() {
    if (window->algorithmThread) {
      window->endThread = true;
      window->algorithmThread->join();
      delete window->algorithmThread;

      switch (window->buttonWidget->getAlgorithm()) {
        case Widget::FR :window->algorithm = new FruchtermanReingold(window->graph);
          break;
        case Widget::SMPL: window->algorithm = new SFDAdapter(window->graph);
          break;
        case Widget::MLT: window->algorithm = new MultiForce(window->graph);
          break;
        default: break;
      }

      window->endThread = false;
      window->algorithmThread = new thread(GLWindow::algorithmFunction);
    }
  }

};

#endif //NETVIZGL_REFRESHGRAPHCOMMAND_H
