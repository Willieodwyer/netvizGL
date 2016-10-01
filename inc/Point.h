//
// Created by werl on 23/09/16.
//

#ifndef NETVIZGL_SPHERE_H
#define NETVIZGL_SPHERE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>
#include "Renderable.h"

class Point : public Renderable {
public:

    GLuint *indices;
    GLint indIndex;

    Point(float radius, unsigned int rings, unsigned int sectors, float offsetX, float offsetY, float offsetZ);

    virtual ~Point();

    void draw();
};


#endif //NETVIZGL_SPHERE_H
