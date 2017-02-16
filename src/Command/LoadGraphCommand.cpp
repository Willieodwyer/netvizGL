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
#include "../../inc/Algorithms/FruchtermanReingold.h"

LoadGraphCommand::LoadGraphCommand(GLWindow *window)
    : window(window) {}

void LoadGraphCommand::execute() {
  std::ifstream infile;
  infile.open(window->graphFilePath);
  std::string sLine;
  getline(infile, sLine);
  infile.close();

  if (window->graph) {
    window->graph->numVertices = 0;
  }
  Graph *temp = window->graph;

  if (sLine.length() <= 4) {
    window->graph = new EdgeGraph((window->graphFilePath));
    fprintf(stdout, "Loading EdgeList:%s\n", window->graphFilePath);

  } else if (strcmp("%%MatrixMarket", sLine.substr(0, 14).c_str()) == 0) /*%%MatrixMarket 14 chars*/{
    window->graph = new MatrixMarketGraph((window->graphFilePath));

    fprintf(stdout, "Loading MatrixMarketGraph:%s\n", window->graphFilePath);

  } else if (sLine.length() > 3 && (strcmp("0", sLine.substr(0, 1).c_str()) == 0)
      || strcmp("1", sLine.substr(0, 1).c_str()) == 0) {
    window->graph = new AdjacencyGraph((window->graphFilePath));
    fprintf(stdout, "Loading AdjacencyGraph:%s\n", window->graphFilePath);

  } else {
    fprintf(stderr, "Error file type not supported?");
    return;
  }

  if (window->algorithmThread) {
    window->endThread = true;
    window->algorithmThread->join();
    delete window->algorithmThread;
  }

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

  char *digit = new char[64];
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
  for (int j = 0; j < GLWindow::Instance()->graph->numVertices; ++j) {
    sprintf(digit, "%d", j);
    //GLWindow::Instance()->graph->vertices[j]->setText(digit);
    GLWindow::Instance()->graph->vertices[j]->setColour(((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)),
                                  ((double) rand() / (RAND_MAX)));
  }
  delete (digit);

  if (temp) {
    delete (temp);
  }
}
