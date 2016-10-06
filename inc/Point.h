//
// Created by werl on 23/09/16.
//

#ifndef NETVIZGL_SPHERE_H
#define NETVIZGL_SPHERE_H

#include <cmath>
#include "Line.h"

class Point{
public:
    static const unsigned int rings = 18, sectors = 18;
    static const double radius = .01;

    Point *attachedPoint;
    void attachPoint(Point *p);

    Line *line = NULL;

    GLdouble colourR;
    GLdouble colourG;
    GLdouble colourB;

    Point(float OFFSETX, float OFFSETY, float OFFSETZ);

    GLdouble offsetX, offsetY, offsetZ;

    GLuint *indices;
    GLint indIndex;

    virtual ~Point();

    void draw();

    void setColour(GLdouble r, GLdouble g, GLdouble b);

    GLdouble *getColour();

    GLdouble *vertices;
    GLdouble  *colours;
};


#endif //NETVIZGL_SPHERE_H
