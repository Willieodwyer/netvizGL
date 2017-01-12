//
// Created by werl on 12/01/17.
//

#include "../../inc/Command/LoadGraphCommand.h"
#include "../../inc/Graphs/EdgeGraph.h"

LoadGraphCommand::LoadGraphCommand(Window *window)
    : window(window){

}

void LoadGraphCommand::execute() {
  window->graph = new EdgeGraph((window->graphFilePath));
  if (window->algorithmThread) {
    window->endThread = true;
    window->algorithmThread->join();
    delete window->algorithmThread;
  }

  window->algorithm = new SimpleForceDirected(Window::Instance()->graph);
  window->endThread = false;
  window->algorithmThread = new thread(Window::algorithmFunction);
}
