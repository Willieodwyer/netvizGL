//
// Created by werl on 29/09/16.
//

#ifndef NETVIZGL_LINE_H
#define NETVIZGL_LINE_H


#include <GL/gl.h>
#include "Renderable.h"

class Line : public Renderable {
public:

    Line(GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X2, GLfloat Y2, GLfloat Z2);

    ~Line();

    void draw();
};


#endif //NETVIZGL_LINE_H
