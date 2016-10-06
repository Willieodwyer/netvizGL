#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "inc/Window.h"

int main(int argc, char **argv) {

    Window *window = Window::Instance();

    if (NULL != window->window) {
        window->display();
        glDisableClientState(GL_COLOR_ARRAY);
    }

    glfwDestroyWindow(window->window);
    glfwTerminate();
    return 0;
}