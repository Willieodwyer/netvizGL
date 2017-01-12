#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "inc/Window.h"
#include "inc/Widget.h"

//static void widget(Widget *x){
//  x = Widget::Instance();
//}

int main(int argc, char **argv) {
  //Widget *buttonWidget;


  Window *window = Window::Instance();

  //std::thread widgetThread(widget, buttonWidget);

  if (NULL != window->window) {
    window->display();
    glDisableClientState(GL_COLOR_ARRAY);
  }

  glfwDestroyWindow(window->window);
  glfwTerminate();
  return 0;
}