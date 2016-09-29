//
// Created by werl on 23/09/16.
//

#ifndef NETVIZGL_SPHERE_H
#define NETVIZGL_SPHERE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>

class Point
{
public:
    GLfloat *verts;

    std::vector<GLushort> indices;

public:
    Point(float radius, unsigned int rings, unsigned int sectors);

    void draw(GLfloat x, GLfloat y, GLfloat z);
};


#endif //NETVIZGL_SPHERE_H
