//
// Created by william on 13/03/17.
//

#ifndef NETVIZGL_DELETEEDGE_H
#define NETVIZGL_DELETEEDGE_H

#include <fstream>
#include "Command.h"
#include "../GLWindow.h"
#include "../Graphs/EdgeGraph.h"
class DeleteEdge : public Command {
 private:
  GLWindow *window;
 public:
  DeleteEdge(GLWindow *window) : window(window) {}
  int deleteEdge;

 public:
  void execute() override {
    if (window->graph && deleteEdge > 0 && deleteEdge < window->graph->numEdges) {

      vector<int *> newEdgeList;
      for (int j = 0; j < window->graph->edgeList.size(); ++j) {
        if (j != deleteEdge) {
          int *temp = new int[2];
          temp[0] = window->graph->edgeList[j][0];
          temp[1] = window->graph->edgeList[j][1];
          cerr << temp[0] << " " << temp[1] << endl;
          newEdgeList.push_back(temp);
        }
      }

      ofstream myfile;
      myfile.open("./LastEditedGraph");
      for (int i = 0; i < newEdgeList.size(); ++i) {
        myfile << newEdgeList[i][0] << " " << newEdgeList[i][1] << endl;
      }
      myfile.close();

      window->graphFilePath = (char *) "./LastEditedGraph";

      if (window->graph) {
        window->graph->numVertices = 1;
      }

      Graph *temp = window->graph;

      window->graph = new EdgeGraph((window->graphFilePath), newEdgeList);
      window->algorithm->graph = window->graph;

      GLdouble *colours = new GLdouble[3];

      for (int i = 0; i < window->graph->numVertices; ++i) {
        window->graph->vertices[i]->posX = temp->vertices[i]->posX;
        window->graph->vertices[i]->posY = temp->vertices[i]->posY;
        window->graph->vertices[i]->posZ = temp->vertices[i]->posZ;

        window->graph->vertices[i]->setText(temp->vertices[i]->text);

        temp->vertices[i]->getColour(colours);
        window->graph->vertices[i]->setColour(colours[0], colours[1], colours[2]);
      }
//      window->algorithmThread = new thread(GLWindow::algorithmFunction);

//      if (temp) {
//        delete (temp);
//      }
    }
  }
};

#endif //NETVIZGL_DELETEEDGE_H
