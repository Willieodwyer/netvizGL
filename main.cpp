#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "inc/Window.h"

void controls(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)

        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
}


int main(int argc, char **argv) {
    Window *window = new Window(1280, 720);
    if (NULL != window->window) {
        window->display();
    }
    glfwDestroyWindow(window->window);
    glfwTerminate();
    return 0;
}