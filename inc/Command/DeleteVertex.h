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

class DeleteVertex : public Command {
 private:
  GLWindow *window;
 public:
  DeleteVertex(GLWindow *window, int deletedNode)
      : window(window), deleteNode(deletedNode) {};
  int deleteNode;

 public:
  void execute() override {
    if (window->graph && deleteNode >= 0 && deleteNode <= window->graph->numVertices) {
      vector<int *> newEdgeList;
      for (int j = 0; j < window->graph->edgeList.size(); ++j) {
        int *temp = new int[2];
        temp[0] = window->graph->edgeList[j][0];
        temp[1] = window->graph->edgeList[j][1];
        newEdgeList.push_back(temp);
      }

      for (int i = 0; i < newEdgeList.size(); ++i) {
        if ((newEdgeList[i][0] == deleteNode ||
            newEdgeList[i][1] == deleteNode)) {
          newEdgeList.erase(newEdgeList.begin() + i);
          i--;
        }
      }

      for (int i = 0; i < newEdgeList.size(); ++i) {
        if (newEdgeList[i][0] > deleteNode)
          newEdgeList[i][0]--;
        if (newEdgeList[i][1] > deleteNode)
          newEdgeList[i][1]--;
      }

      ofstream myfile;
      myfile.open("./LastEditedGraph");
      for (int i = 0; i < newEdgeList.size(); ++i) {
        myfile << newEdgeList[i][0] << " " << newEdgeList[i][1] << endl;
      }
      myfile.close();

      window->graphFilePath = (char *) "./LastEditedGraph";

      std::ifstream infile;
      infile.open(window->graphFilePath);
      std::string sLine;
      getline(infile, sLine);
      infile.close();

      if (window->graph) {
        window->graph->numVertices = 1;
      }

      Graph *temp = window->graph;

      if (sLine.length() <= 4) {
        window->graph = new EdgeGraph((window->graphFilePath), newEdgeList);
        //fprintf(stdout, "Loading EdgeList:%s\n", window->graphFilePath);
      }
      window->algorithm->graph = window->graph;

//      if (window->algorithmThread) {
//        window->endThread = true;
//        window->algorithmThread->join();
//        delete window->algorithmThread;
//      }
//
//      switch (window->buttonWidget->getAlgorithm()) {
//        case Widget::FR :window->algorithm = new FruchtermanReingold(window->graph);
//          break;
//        case Widget::SMPL: window->algorithm = new SimpleForceDirected(window->graph);
//          break;
//        case Widget::MLT: window->algorithm = new MultiLevel(window->graph);
//          break;
//        default: break;
//      }
//      window->endThread = false;

      GLdouble *colours = new GLdouble[3];

      for (int i = 0; i < deleteNode; ++i) {
        window->graph->vertices[i]->posX = temp->vertices[i]->posX;
        window->graph->vertices[i]->posY = temp->vertices[i]->posY;
        window->graph->vertices[i]->posZ = temp->vertices[i]->posZ;

        window->graph->vertices[i]->setText(temp->vertices[i]->text);

        temp->vertices[i]->getColour(colours);
        window->graph->vertices[i]->setColour(colours[0], colours[1], colours[2]);
      }

      for (int k = deleteNode; k < window->graph->numVertices; ++k) {
        window->graph->vertices[k]->posX = temp->vertices[k + 1]->posX;
        window->graph->vertices[k]->posY = temp->vertices[k + 1]->posY;
        window->graph->vertices[k]->posZ = temp->vertices[k + 1]->posZ;

        window->graph->vertices[k]->setText(temp->vertices[k + 1]->text);

        temp->vertices[k + 1]->getColour(colours);
        window->graph->vertices[k]->setColour(colours[0], colours[1], colours[2]);
      }

//      window->algorithmThread = new thread(GLWindow::algorithmFunction);

//      if (temp) {
//        delete (temp);
//      }
    }
  }
};

#endif //NETVIZGL_UPDATEGRAPH_H
