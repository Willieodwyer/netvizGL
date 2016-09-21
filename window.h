//
// Created by werl on 21/09/16.
//

#ifndef NETVIZGL_WINDOW_H
#define NETVIZGL_WINDOW_H

#include <GLFW/glfw3.h>

class Window {
public:
    GLFWwindow *window;

    int windowWidth;
    int windowHeight;

    Window(const int WIDTH, const int HEIGHT);
    ~Window();

    void display();

    void draw();
};


#endif //NETVIZGL_WINDOW_H
