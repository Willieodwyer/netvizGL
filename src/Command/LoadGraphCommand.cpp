//
// Created by werl on 12/01/17.
//

#include "../../inc/Command/LoadGraphCommand.h"
#include "../../inc/Graphs/EdgeGraph.h"
#include "../../inc/Graphs/MatrixMarketGraph.h"

LoadGraphCommand::LoadGraphCommand(GLWindow *window)
    : window(window) {

}

void LoadGraphCommand::execute() {
  if(window->graph){
    delete(window->graph);
  }

  window->graph = new EdgeGraph((window->graphFilePath));
  if (window->algorithmThread) {
    window->endThread = true;
    window->algorithmThread->join();
    delete window->algorithmThread;
  }

  window->algorithm = new SimpleForceDirected(GLWindow::Instance()->graph);
  window->endThread = false;
  window->algorithmThread = new thread(GLWindow::algorithmFunction);


}
