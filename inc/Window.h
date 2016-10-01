//
// Created by werl on 21/09/16.
//

#ifndef NETVIZGL_WINDOW_H
#define NETVIZGL_WINDOW_H

#include <GLFW/glfw3.h>
#include "Point.h"

class Window {
public:
    GLFWwindow *window;
    Renderable *point;
    Renderable *point2;
    Renderable *point3;
    Renderable *point4;
    Renderable *line;

    int windowWidth;
    int windowHeight;

    Window(const int WIDTH, const int HEIGHT);

    ~Window();

    void display();

};

#endif //NETVIZGL_WINDOW_H
