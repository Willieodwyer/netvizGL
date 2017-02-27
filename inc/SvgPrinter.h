//
// Created by william on 01/02/17.
//
#ifndef NETVIZGL_SVGPRINTER_H
#define NETVIZGL_SVGPRINTER_H

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
};

void SvgPrinter::printGraph(Graph *g, double translateZ) {
  if (g) {
    for (int i = 0; i < g->numVertices; ++i) {
      printLine(g->vertices[i]);
    }
    for (int i = 0; i < g->numVertices; ++i) {
      printVertex(g->vertices[i]);
    }
    for (int i = 0; i < g->numVertices; ++i) {
      printText(g->vertices[i]);
    }
    doc->save();
  }
}

inline void SvgPrinter::printVertex(Vertex *v) {
  GLdouble *pos = new GLdouble[3];
  GLdouble *colours = new GLdouble[3];

  v->getScreenPosition(pos);
  v->getColour(colours);

  if (pos[0] >= -tolerance && pos[0] - tolerance <= dimensions->width
      && pos[1] >= -tolerance && pos[1] - tolerance <= dimensions->height) {
    *doc << Circle(Point(pos[0], pos[1]), 180 * (1 - pos[2]),
                   Fill(Color((int) (colours[0] * 256), (int) (colours[1] * 256), (int) (colours[2] * 256))),
                   Stroke(0, Color(200, 250, 150)));
  }
  delete (pos);
  delete (colours);
}

inline void SvgPrinter::printLine(Vertex *v) {
  GLdouble *pos = new GLdouble[3];
  GLdouble *attachedPos = new GLdouble[3];

  v->getScreenPosition(pos);
  if (pos[0] >= -tolerance && pos[0] - tolerance <= dimensions->width
      && pos[1] >= -tolerance && pos[1] - tolerance <= dimensions->height) {
    for (int i = 0; i < v->attachedPoints.size(); ++i) {
      v->attachedPoints[i]->getScreenPosition(attachedPos);
      *doc << (svg::Line(Point(pos[0], pos[1]), Point(attachedPos[0], attachedPos[1]),
                         Stroke(1, Color((int) (v->edges[i]->colours[0] * 256),
                                         (int) (v->edges[i]->colours[1] * 256),
                                         (int) (v->edges[i]->colours[2] * 256)))));
    }

    delete (pos);
    delete (attachedPos);
  }
}

void SvgPrinter::printText(Vertex *v) {
  if (v->text) {
    GLdouble *pos = new GLdouble[3];
    GLdouble *basePos = new GLdouble[3];
    GLdouble *connectPos = new GLdouble[3];

    v->getScreenPosition(pos);
    if (pos[0] >= -tolerance && pos[0] - tolerance <= dimensions->width
        && pos[1] >= -tolerance && pos[1] - tolerance <= dimensions->height) {
      *doc << Text(Point(pos[0], pos[1]), v->text, Color::Black, svg::Font(100 * (1 - pos[2]), "Arial"));
      for (int i = 0; i < v->edges.size(); ++i) {
        v->edges[i]->base->getScreenPosition(basePos);
        v->edges[i]->connect->getScreenPosition(connectPos);

        double midX = basePos[0] + connectPos[0];
        midX = midX / 2;

        double midY = basePos[1] + connectPos[1];
        midY = midY / 2;

        double midZ = basePos[2] + connectPos[2];
        midZ = midZ / 2;

        *doc
            << Text(Point(midX + 5, midY + 5), v->edges[i]->text, Color::Black, svg::Font(100 * (1 - pos[2]), "Arial"));
      }
    }
    delete (pos);
  }
}
}

//    *doc << (svg::Edge(Point(600, 300), Point(600, 200), Stroke(2, Color::Black)));
//    *doc << Circle(Point(600, 300), 10, Fill(Color(100, 200, 120)), Stroke(0, Color(200, 250, 150)));
//    *doc << Text(Point(600, 300), "Some Data", Color::Black, svg::Font(9, "Arial"));
//  doc->save();

#endif //NETVIZGL_SVGPRINTER_H