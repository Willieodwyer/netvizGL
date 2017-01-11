#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "inc/Window.h"
#include "inc/ButtonWidget.h"

//static void widget(ButtonWidget *x){
//  x = ButtonWidget::Instance();
//}

int main(int argc, char **argv) {
  //ButtonWidget *buttonWidget;


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