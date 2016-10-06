//
// Created by werl on 01/10/16.
//

#ifndef NETVIZGL_RENDERABLE_H
#define NETVIZGL_RENDERABLE_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>

class Renderable {
public:

    GLdouble *vertices;
    GLdouble  *colours;

    Renderable() {
        fprintf(stdout, "Made a renderable!\n");
    };

    virtual ~Renderable() { delete vertices; };

    virtual void draw()= 0;

};

#endif //NETVIZGL_RENDERABLE_H
