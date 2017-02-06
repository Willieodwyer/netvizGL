//
// Created by werl on 12/01/17.
//

#include <fstream>
#include "../../inc/Command/LoadGraphCommand.h"
#include "../../inc/Graphs/EdgeGraph.h"
#include "../../inc/Graphs/MatrixMarketGraph.h"
#include "../../inc/Graphs/AdjacencyGraph.h"
#include "../../inc/Algorithms/SimpleForceDirected.h"
#include "../../inc/Algorithms/MultiLevel.h"

LoadGraphCommand::LoadGraphCommand(GLWindow *window)
    : window(window) {}

void LoadGraphCommand::execute() {
  std::ifstream infile;
  infile.open(window->graphFilePath);
  std::string sLine;
  getline(infile, sLine);
  infile.close();

  Graph *temp = window->graph;

  if (sLine.length() <= 4) {
    window->graph = new EdgeGraph((window->graphFilePath));
    fprintf(stderr, "Loading EdgeList:%s\n", window->graphFilePath);

  } else if (strcmp("%%MatrixMarket", sLine.substr(0, 14).c_str()) == 0) /*%%MatrixMarket 14 chars*/{
    window->graph = new MatrixMarketGraph((window->graphFilePath));

    fprintf(stderr, "Loading MatrixMarketGraph:%s\n", window->graphFilePath);

  } else if (sLine.length() > 3 && (strcmp("0", sLine.substr(0, 1).c_str()) == 0)
      || strcmp("1", sLine.substr(0, 1).c_str()) == 0) {
    window->graph = new AdjacencyGraph((window->graphFilePath));
    fprintf(stderr, "Loading AdjacencyGraph:%s\n", window->graphFilePath);

  } else {
    fprintf(stderr, "Error file type not supported?");
    exit(0);
  }

  if (window->algorithmThread) {
    window->endThread = true;
    window->algorithmThread->join();
    delete window->algorithmThread;
  }

  window->algorithm = new SimpleForceDirected(GLWindow::Instance()->graph);
  window->endThread = false;
  window->algorithmThread = new thread(GLWindow::algorithmFunction);

  if (temp) {
    delete (temp);
  }
}
