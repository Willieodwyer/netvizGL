//
// Created by william on 15/02/17.
//

#include "../../inc/Command/RefreshGraphCommand.h"
#include "../../inc/Algorithms/FruchtermanReingold.h"
#include "../../inc/Algorithms/SimpleForceDirected.h"
#include "../../inc/Algorithms/MultiLevel.h"

RefreshGraphCommand::RefreshGraphCommand(GLWindow *window) : window(window) {}

void RefreshGraphCommand::execute() {
  if (window->algorithmThread) {
    window->endThread = true;
    window->algorithmThread->join();
    delete window->algorithmThread;

    switch (Widget::getAlgorithm()) {
      case Widget::FR :window->algorithm = new FruchtermanReingold(GLWindow::Instance()->graph);
        break;
      case Widget::SMPL: window->algorithm = new SimpleForceDirected(GLWindow::Instance()->graph);
        break;
      case Widget::MLT: window->algorithm = new MultiLevel(GLWindow::Instance()->graph);
        break;
      default: break;
    }

    window->endThread = false;
    window->algorithmThread = new thread(GLWindow::algorithmFunction);

  }
}
