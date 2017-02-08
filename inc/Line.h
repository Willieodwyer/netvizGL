//
// Created by werl on 29/09/16.
//

#ifndef NETVIZGL_LINE_H
#define NETVIZGL_LINE_H
#include <GL/glew.h>

class Line
{
public:

    GLdouble posX1, posY1, posZ1;
    GLdouble posX2, posY2, posZ2;

    Line(GLdouble X1, GLdouble Y1, GLdouble Z1, GLdouble X2, GLdouble Y2, GLdouble Z2);

    ~Line();

    GLdouble *vertices;

    GLfloat *colors;

    void draw();

    void setColour(GLfloat r, GLfloat g, GLfloat b, GLfloat r2, GLfloat g2, GLfloat b2);
    void update();

    static const double scale;
};

#endif //NETVIZGL_LINE_H
