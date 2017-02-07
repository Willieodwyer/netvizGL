//
// Created by william on 01/02/17.
//
#ifndef NETVIZGL_SVGPRINTER_H
#define NETVIZGL_SVGPRINTER_H

#include <algorithm>
#include "Vertex.h"
#include "SimpleSvg.h"
#include "Graphs/Graph.h"

namespace svg {

class SvgPrinter {
 private:
  char *name;
  Document *doc;
  Dimensions *dimensions;
 public:
  static constexpr GLdouble tolerance = 200;

  SvgPrinter(Document *doc, Dimensions *dimensions) : doc(doc), dimensions(dimensions) {
    Polygon border(Stroke(1, Color::Silver));
    border << Point(0, 0) << Point(dimensions->width, 0)
           << Point(dimensions->width, dimensions->height) << Point(0, dimensions->height);
    *doc << border;
  }
  void printGraph(Graph *g, double translateZ);
  inline void printVertex(Vertex *v);
  inline void printLine(Vertex *v);
  inline void printText(Vertex *v);
  static bool depthFunc(Vertex *u, Vertex *v);

};

void SvgPrinter::printGraph(Graph *g, double translateZ) {
  if (g) {
    vector<Vertex *> orderedVertices;
    for (int j = 0; j < g->numVertices; ++j) {
      orderedVertices.push_back(g->vertices[j]);
    }

    for (int i = 0; i < g->numVertices; ++i) {
      printLine(orderedVertices[i]);
    }
    for (int i = 0; i < g->numVertices; ++i) {
      printVertex(orderedVertices[i]);
    }
    for (int i = 0; i < g->numVertices; ++i) {
      printText(orderedVertices[i]);
    }
    doc->save();
  }
}

inline void SvgPrinter::printVertex(Vertex *v) {
  GLdouble *pos = new GLdouble[3];
  v->getScreenPosition(pos);

  if (pos[0] >= -tolerance && pos[0] - tolerance <= dimensions->width
      && pos[1] >= -tolerance && pos[1] - tolerance <= dimensions->height) {
    *doc << Circle(Point(pos[0], pos[1]), 90 * (2 * (1 - pos[2])),
                   Fill(Color((int) (v->colourR * 256), (int) (v->colourG * 256), (int) (v->colourB * 256))),
                   Stroke(0, Color(200, 250, 150)));
  }
  delete (pos);
}

inline void SvgPrinter::printLine(Vertex *v) {
  GLdouble *pos = new GLdouble[3];
  GLdouble *attachedPos = new GLdouble[3];

  v->getScreenPosition(pos);

  if (pos[0] >= -tolerance && pos[0] - tolerance <= dimensions->width
      && pos[1] >= -tolerance && pos[1] - tolerance <= dimensions->height) {
    for (int i = 0; i < v->attachedPoints.size(); ++i) {
      v->attachedPoints[i]->getScreenPosition(attachedPos);
      *doc << (svg::Line(Point(pos[0], pos[1]), Point(attachedPos[0], attachedPos[1]), Stroke(1, Color::Black)));
    }
  }

  delete (pos);
  delete (attachedPos);
}

void SvgPrinter::printText(Vertex *v) {
  if (v->text) {
    GLdouble *pos = new GLdouble[3];
    v->getScreenPosition(pos);
    if (pos[0] >= -tolerance && pos[0] - tolerance <= dimensions->width
        && pos[1] >= -tolerance && pos[1] - tolerance <= dimensions->height) {
      *doc << Text(Point(pos[0], pos[1]), v->text, Color::Black, svg::Font(100 * (1 - pos[2]), "Arial"));
    }
    delete (pos);
  }
}
bool SvgPrinter::depthFunc(Vertex *u, Vertex *v) {
  GLdouble vpos[3];
  v->getScreenPosition(vpos);
  GLdouble upos[3];
  v->getScreenPosition(upos);

  return upos[2] > vpos[2];
}
}

#endif //NETVIZGL_SVGPRINTER_H