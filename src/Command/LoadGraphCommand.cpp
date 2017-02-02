//
// Created by werl on 12/01/17.
//

#include "../../inc/Command/LoadGraphCommand.h"
#include "../../inc/Graphs/EdgeGraph.h"
#include "../../inc/Graphs/MatrixMarketGraph.h"
#include "../../inc/Algorithms/MultiLevel.h"

LoadGraphCommand::LoadGraphCommand(GLWindow *window)
    : window(window) {

}

void LoadGraphCommand::execute() {
  Graph *temp = window->graph;

  window->graph = new MatrixMarketGraph((window->graphFilePath));
  if (window->algorithmThread) {
    window->endThread = true;
    window->algorithmThread->join();
    delete window->algorithmThread;
  }

  window->algorithm = new MultiLevel(GLWindow::Instance()->graph);
  window->endThread = false;
  window->algorithmThread = new thread(GLWindow::algorithmFunction);

  if(temp){
    delete(temp);
  }
}
