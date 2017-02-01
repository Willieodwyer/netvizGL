//
// Created by william on 01/02/17.
//
#ifndef NETVIZGL_SVGVERTEXPRINTER_H
#define NETVIZGL_SVGVERTEXPRINTER_H

#include "SimpleSvg.hpp"
#include "Vertex.h"

using namespace svg;

class SvgPrinter {
 private:
  char *name;
 public:
  SvgPrinter(char *filePath, int width, int height) : name(filePath) {
//    Dimensions dimensions = Dimensions(width, height);
//    Document doc = Document("SVGTEST.svg", Layout(dimensions, Layout::BottomLeft));
//
//    Polygon border(Stroke(1, Color::Silver));
//    border << Point(0, 0) << Point(dimensions.width, 0)
//           << Point(dimensions.width, dimensions.height) << Point(0, dimensions.height);
//    doc << border;
//    doc << (svg::Line(Point(600, 300),Point(600, 200),Stroke(2, Color::Black)));
//    doc << Circle(Point(600, 300), 10, Fill(Color(100, 200, 120)), Stroke(0, Color(200, 250, 150)));
//    doc << Circle(Point(600, 200), 10, Fill(Color(0, 256, 256)), Stroke(0, Color(200, 250, 150)));
//    doc << Text(Point(600, 300), "Some Data", Color::Black, svgFont(9, "Arial"));
//    doc.save();
  }

  void printVertex(Vertex *v);
};

void SvgPrinter::printVertex(Vertex *v) {

}

#endif //NETVIZGL_SVGVERTEXPRINTER_H
