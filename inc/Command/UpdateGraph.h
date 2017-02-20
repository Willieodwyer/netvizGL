//
// Created by william on 20/02/17.
//

#ifndef NETVIZGL_UPDATEGRAPH_H
#define NETVIZGL_UPDATEGRAPH_H

#include "Command.h"
#include "../GLWindow.h"
#include "../Graphs/EdgeGraph.h"
#include "../Algorithms/FruchtermanReingold.h"
#include "../Algorithms/SimpleForceDirected.h"
#include "../Algorithms/MultiLevel.h"
#include <fstream>

class UpdateGraph : public Command {
 private:
  GLWindow *window;
 public:
  UpdateGraph(GLWindow *window, int deletedNode)
      : window(window), deletedNode(deletedNode) {};
  int deletedNode;

 public:
  void execute() override {
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

    }

    if (window->algorithmThread) {
      window->endThread = true;
      window->algorithmThread->join();
      delete window->algorithmThread;
    }

    switch (window->buttonWidget->getAlgorithm()) {
      case Widget::FR :window->algorithm = new FruchtermanReingold(window->graph);
        break;
      case Widget::SMPL: window->algorithm = new SimpleForceDirected(window->graph);
        break;
      case Widget::MLT: window->algorithm = new MultiLevel(window->graph);
        break;
      default: break;
    }
    window->endThread = false;

    GLdouble *colours = new GLdouble[3];

    for (int i = 0; i < deletedNode; ++i) {
      window->graph->vertices[i]->posX = temp->vertices[i]->posX;
      window->graph->vertices[i]->posY = temp->vertices[i]->posY;
      window->graph->vertices[i]->posZ = temp->vertices[i]->posZ;

      temp->vertices[i]->getColour(colours);
      window->graph->vertices[i]->setColour(colours[0], colours[1], colours[2]);
      cout << colours[0] << "," << colours[1] << "," << colours[2] << endl;
    }

    for (int k = deletedNode; k < window->graph->numVertices; ++k) {
      window->graph->vertices[k]->posX = temp->vertices[k + 1]->posX;
      window->graph->vertices[k]->posY = temp->vertices[k + 1]->posY;
      window->graph->vertices[k]->posZ = temp->vertices[k + 1]->posZ;

      temp->vertices[k + 1]->getColour(colours);
      window->graph->vertices[k]->setColour(colours[0], colours[1], colours[2]);
      cout << colours[0] << "," << colours[1] << "," << colours[2] << endl;
    }

    window->algorithmThread = new thread(GLWindow::algorithmFunction);

//    char *digit = new char[64];
//    struct timeval time;
//    gettimeofday(&time, NULL);
//    srand(Graph::hash3(time.tv_sec, time.tv_usec, getpid()));
//    for (int j = 0; j < window->graph->numVertices; ++j) {
//      sprintf(digit, "%d", j);
//      //GLWindow::Instance()->graph->vertices[j]->setText(digit);
//    }
//    delete (digit);

    if (temp) {
      delete (temp);
    }

  }
};

#endif //NETVIZGL_UPDATEGRAPH_H
