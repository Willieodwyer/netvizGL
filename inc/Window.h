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

    void GLinit();

    static void keyPressedEvent(GLFWwindow *window, int key, int scancode, int action, int mode);
};

#endif //NETVIZGL_WINDOW_H
