//
// Created by werl on 29/09/16.
//

#ifndef NETVIZGL_LINE_H
#define NETVIZGL_LINE_H


#include <GL/gl.h>

class Line {
public:

    Line(GLdouble X1, GLdouble Y1, GLdouble Z1, GLdouble X2, GLdouble Y2, GLdouble Z2);

    ~Line();
    GLdouble *vertices;
    void draw();
};


#endif //NETVIZGL_LINE_H
