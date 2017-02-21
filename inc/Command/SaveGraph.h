//
// Created by werl on 16/02/17.
//

#ifndef NETVIZGL_SAVEGRAPH_H
#define NETVIZGL_SAVEGRAPH_H

#include <X11/Xlib.h>
#include <iostream>
#include <pngwriter.h>
#include <X11/Xutil.h>
#include <fstream>
#include "Command.h"

class SaveGraph : public Command {
 private:
  GLWindow *window;
  Widget::SaveAsFileType fileType;
  char *name;

 public:
  SaveGraph(GLWindow *window, Widget::SaveAsFileType type, char *fileName)
      : window(window), fileType(type), name(fileName) {};

  void execute() override {
    switch (fileType) {
      case Widget::ADJACENCY: saveAdjacency();
        break;
      case Widget::EDGELIST: saveEdgeList();
        break;
      case Widget::PNG: savePNG();
        break;
      case Widget::SVG: saveSVG();
        break;
      default: break;
    }
  }

  void saveAdjacency() {
    if (window->graph) {
      ofstream file;
      file.open(name);
      for (int i = 0; i < window->graph->numVertices; ++i) {
        for (int j = 0; j < window->graph->numVertices; ++j) {
          file << window->graph->adjacencyMatrix[i][j];
          if (j < (window->graph->numVertices - 1))
            file << " ";
        }
        file << endl;
      }
      file.close();
    }
  }

  void saveEdgeList() {
    if (window->graph) {
      ofstream file;
      file.open(name);
      for (int i = 0; i < window->graph->edgeList.size(); ++i) {
        file << window->graph->edgeList[i][0] << " " << window->graph->edgeList[i][1] << endl;
      }
      file.close();
    }
  }

  void savePNG() {
    window->X11Screenshot(name);
  }
  void saveSVG() {
    window->svgFileName = name;
    window->takeSvgScreen = true;
  }
};

#endif //NETVIZGL_SAVEGRAPH_H
