#include <GL/glew.h>
#include <iostream>
#include "../inc/Window.h"
#include "../inc/FileReader.h"
#include "../inc/Graphs/EdgeGraph.h"
#include <glm/geometric.hpp>
#include <pngwriter.h>

//
// Created by werl on 21/09/16.
//
Window *Window::windowInstance = NULL;

Window *Window::Instance() {
  if (!windowInstance)
    windowInstance = new Window(1280, 720);
  return windowInstance;
}

Window::Window(const int WIDTH, const int HEIGHT) {
  screenShot = false;
  fullscreen = false;

  pitch = 0;
  yaw = 0;
  bank = 0;

  translateX = 0;
  translateY = 0;
  translateZ = 1;

  mouseLEFT = false;
  mouseRIGHT = false;

  this->windowWidth = WIDTH;
  this->windowHeight = HEIGHT;

  GLInit();

  //GTK Widget
  //Window::Instance()->widgetThread = new thread(widget, Window::Instance()->buttonWidget);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glEnable(GL_CULL_FACE);
}

//Threads
void Window::Apply() {
  while (!Window::Instance()->endThread) {
    Window::Instance()->algorithm->apply();
  }
}

void Window::widget(ButtonWidget *x) {
  x = ButtonWidget::Instance();
  //fprintf(stderr,"HEREER");
}
//

void Window::display() {
  while (!glfwWindowShouldClose(window)) {
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    glClearColor(0.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluPerspective(45, (double) windowWidth / (double) windowHeight, .1, 100);

    //menu->draw();

    glTranslatef((GLfloat) translateX, (GLfloat) translateY, (GLfloat) -translateZ);

    glRotatef((GLfloat) pitch, 1, 0, 0);   //pitch
    glRotatef((GLfloat) yaw, 0, 1, 0);     //yaw

    if (Graph::numGraphs != 0) {
      graph->update();
      graph->draw();
    }

    glLineWidth(4.0);

    if (screenShot) {
      screenshot();
      screenShot = false;
    }

    glfwSwapBuffers(window);

    glfwPollEvents();
  }
}

void Window::GLInit() {

  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
  }
  glfwWindowHint(GLFW_SAMPLES, 8);

  // Open a window and create its OpenGL context

  if (!Window::fullscreen)
    window = glfwCreateWindow(windowWidth, windowHeight, "netvizGL", NULL, NULL);
  else {
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(mode->width, mode->height, "netvizGL", glfwGetPrimaryMonitor(), window);
  }

  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);

  glfwSetWindowPos(window, 320, 180);

  glewExperimental = GL_TRUE;

  GLenum err = glewInit();

  if (GLEW_OK != err) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }

  glfwSetKeyCallback(window, keyPressedEvent);
  glfwSetMouseButtonCallback(window, mousePressedEvent);
  glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

  glfwSetCursorPosCallback(window, mousePositionEvent);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  glfwSetScrollCallback(window, this->scrollEvent);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

}

void Window::scrollEvent(GLFWwindow *window, double xoffset, double yoffset) {
  Window::Instance()->translateZ += yoffset / 16;
}

void Window::mousePressedEvent(GLFWwindow *window, int button, int action, int mods) {

  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    Window::Instance()->mouseRIGHT = true;
    //printf("GLFW_MOUSE_BUTTON_RIGHT::%d\n",Window::Instance()->mouseRIGHT);
  }
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
    Window::Instance()->mouseRIGHT = false;
    //printf("GLFW_MOUSE_BUTTON_RIGHT::%d\n",Window::Instance()->mouseRIGHT);
  }

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    Window::Instance()->mouseLEFT = true;
    //printf("GLFW_MOUSE_BUTTON_LEFT::%d\n",Window::Instance()->mouseLEFT);
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    Window::Instance()->mouseLEFT = false;
    //printf("GLFW_MOUSE_BUTTON_LEFT::%d\n",Window::Instance()->mouseLEFT);
  }
}

void Window::mousePositionEvent(GLFWwindow *window, double xpos, double ypos) {

  if (Window::Instance()->mouseLEFT || Window::Instance()->mouseRIGHT) {
    Window::Instance()->yaw += (xpos - Window::Instance()->mouseX) / 8;
    Window::Instance()->pitch += (ypos - Window::Instance()->mouseY) / 8;
    Window::Instance()->mouseX = xpos;
    Window::Instance()->mouseY = ypos;
  }

  Window::Instance()->mouseX = xpos;
  Window::Instance()->mouseY = ypos;
}

void Window::keyPressedEvent(GLFWwindow *window, int key, int scancode, int action, int mode) {

  //printf("Window::keyPressedEvent::%d\n", key);

  if (key == GLFW_KEY_T && action == GLFW_PRESS) {
    if ((Window::Instance()->widgetThread)) {
      ButtonWidget::Instance()->toggleView();
    }
    else{
      Window::Instance()->widgetThread = new thread(widget, Window::Instance()->buttonWidget);
      fprintf(stderr,"HERE");
    }
  }

  if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
    Window::Instance()->screenShot = true;

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
    Window::Instance()->endThread = true;
    Window::Instance()->applyThread->join();
  }

//  if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
//    std::string filePath = FileReader::openFile("zenity --file-selection > temp").c_str();
//    Window::Instance()->graph = new EdgeGraph((char *) filePath.c_str());
//    //graph = new EdgeGraph("../Graphs/edge-links2.txt");
//    //graph = new EdgeGraph("../Graphs/edge-links.txt");
//    Window::Instance()->algorithm = new SimpleForceDirected(Window::Instance()->graph);
//    Window::Instance()->endThread = false;
//    Window::Instance()->applyThread = new thread(Apply);
//  }

  if (key == GLFW_KEY_LEFT) {
    Window::Instance()->translateX += .01;
  }
  if (key == GLFW_KEY_RIGHT) {
    Window::Instance()->translateX -= .01;
  }

  if (key == GLFW_KEY_DOWN) {
    Window::Instance()->translateY += .01;
  }
  if (key == GLFW_KEY_UP) {
    Window::Instance()->translateY -= .01;
  }

}

int Window::screenshot() {

//  fullscreen = true;
//
//  GLInit();
//
//  system("scrot");

  const int pix = 3 * windowWidth * windowHeight;
  GLfloat *pixels = new GLfloat[pix];

  glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_FLOAT, pixels);
  pngwriter PNG(windowWidth, windowHeight, 0.0, "screenshot.png");
  size_t x = 1;
  size_t y = 1;
  double R, G, B;
  for (size_t i = 0; i < pix; i++) {
    switch (i % 3) {
      case 2:B = (double) pixels[i];
        break;
      case 1:G = (double) pixels[i];
        break;
      case 0:R = (double) pixels[i];
        PNG.plot(x, y, R, G, B);
        if (x == windowWidth) {
          x = 1;
          y++;
        } else { x++; }
        break;
    }
  }
  PNG.close();

  delete[] pixels;


//  for(int i = 0; i < pix; i ++){
//    std::cout << pixels[i];Z
//  }
}


