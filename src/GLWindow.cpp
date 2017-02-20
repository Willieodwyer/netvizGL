#include <GL/glew.h>
#include <iostream>
#include "../inc/GLWindow.h"
#include "../inc/Command/LoadGraph.h"
#include "../inc/Command/ColourNode.h"
#include "../inc/Command/TextNode.h"
#include "../inc/Command/RefreshGraph.h"
#include "../inc/SimpleSvg.h"
#include "../inc/SvgPrinter.h"
#include "../inc/Command/DeleteNode.h"
#include <glm/geometric.hpp>
#include <pngwriter.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

//
// Created by werl on 21/09/16.
//
GLWindow *GLWindow::windowInstance = NULL;

GLWindow *GLWindow::Instance() {
  if (!windowInstance)
    windowInstance = new GLWindow(1280, 720);
  return windowInstance;
}

GLWindow::GLWindow(const int WIDTH, const int HEIGHT) {
  screenShot = false;

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

  init();

  //GTK Widget
  widgetThread = new thread(widgetFunction, buttonWidget);

  //Graph command
  loadGraph = new LoadGraph(this);
  updateGraph = new DeleteNode(this,-1);
  colourNode = new ColourNode(this);
  textNode = new TextNode(this);
  refreshGraph = new RefreshGraph(this);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glEnable(GL_CULL_FACE);
}

//Threads
void GLWindow::algorithmFunction() {
  while (!GLWindow::Instance()->endThread && GLWindow::Instance()->graph
      && !glfwWindowShouldClose(GLWindow::Instance()->window)) {
    GLWindow::Instance()->algorithm->apply();
  }
}

void GLWindow::widgetFunction(Widget *x) {
  x = Widget::Ins();
}
//^ Threads

void GLWindow::render() {
  glfwGetWindowSize(window, &windowWidth, &windowHeight);
  glViewport(0, 0, windowWidth, windowHeight);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluPerspective(45, (double) windowWidth / (double) windowHeight, .1, 100);

  glTranslatef((GLfloat) translateX, (GLfloat) translateY, (GLfloat) -translateZ);

  glRotatef((GLfloat) pitch, 1, 0, 0);   //pitch
  glRotatef((GLfloat) yaw, 0, 1, 0);     //yaw

  if (graph != NULL) {
    graph->update();
    graph->draw();
  }

  glLineWidth(2.0);

  glLineWidth(2.0);

  glfwSwapBuffers(window);

  glfwPollEvents();

  if (takeSvgScreen) {
    takeSvgScreen = false;
    svgScreenshot(svgFileName);
  }
}

void GLWindow::init() {

  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
  }
  glfwWindowHint(GLFW_SAMPLES, 8);

  // Open a window and create its OpenGL context

  window = glfwCreateWindow(windowWidth, windowHeight, "netvizGL", NULL, NULL);
//  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
//  window = glfwCreateWindow(2560, 1440, "netvizGL", glfwGetPrimaryMonitor(), window);

  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);

  glfwSetWindowPos(window, 470, 180);

  glewExperimental = GL_TRUE;

  GLenum err = glewInit();

  if (GLEW_OK != err) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }

  glfwSetWindowUserPointer(window, this);
  glfwSetKeyCallback(window, keyPressedEvent);

  glfwSetMouseButtonCallback(window, mousePressedEvent);
  glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

  glfwSetCursorPosCallback(window, mousePositionEvent);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  glfwSetScrollCallback(window, this->scrollEvent);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glClearColor(1.0, 1.0, 1.0, 1.0);

}

void GLWindow::scrollEvent(GLFWwindow *window, double xoffset, double yoffset) {
  static GLWindow *wind = (GLWindow *) (glfwGetWindowUserPointer(window));
  wind->translateZ += yoffset / 20;
}

void GLWindow::mousePressedEvent(GLFWwindow *window, int button, int action, int mods) {
  static GLWindow *wind = (GLWindow *) (glfwGetWindowUserPointer(window));

  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    wind->mouseRIGHT = true;
    wind->colourNode->execute();
  }
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
    wind->mouseRIGHT = false;
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    wind->mouseLEFT = true;
  }
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    wind->mouseLEFT = false;
  }

  if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
    wind->textNode->execute();
  }
}

void GLWindow::mousePositionEvent(GLFWwindow *window, double xpos, double ypos) {
  static GLWindow *wind = (GLWindow *) (glfwGetWindowUserPointer(window));

  if (wind->mouseLEFT) {
    wind->yaw += (xpos - wind->mouseX) / 8;
    wind->pitch += (ypos - wind->mouseY) / 8;
    wind->mouseX = xpos;
    wind->mouseY = ypos;
  }
  wind->mouseX = xpos;
  wind->mouseY = ypos;
}

void GLWindow::keyPressedEvent(GLFWwindow *window, int key, int scancode, int action, int mode) {
  static GLWindow *wind = (GLWindow *) (glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_T && action == GLFW_PRESS) {
    if ((wind->widgetThread)) {
      wind->buttonWidget->toggleView();
    } else {
      fprintf(stderr, "Widget not running");
    }
  }

  if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
    wind->X11Screenshot((char *) "DefaultPng");

  if (key == GLFW_KEY_F6 && action == GLFW_PRESS) {
    wind->svgScreenshot((char *) "DefaultSVG");
  }

  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    DeleteNode *temp = (DeleteNode *) wind->updateGraph;
    temp->deleteNode = 3;
    wind->updateGraph->execute();
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key == GLFW_KEY_LEFT) {
    wind->translateX -= .01;
  }
  if (key == GLFW_KEY_RIGHT) {
    wind->translateX += .01;
  }

  if (key == GLFW_KEY_DOWN) {
    wind->translateY -= .01;
  }
  if (key == GLFW_KEY_UP) {
    wind->translateY += .01;
  }

}

void GLWindow::X11Screenshot(char *file) {
  glfwFocusWindow(window);
  usleep(10000);

  Display *openDisplay = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(openDisplay);
  XWindowAttributes gwa;
  int revert = RevertToNone;
  Window active;
  XGetInputFocus(openDisplay, &active, &revert);

  XGetWindowAttributes(openDisplay, root, &gwa);
  if (!XGetWindowAttributes(openDisplay, active, &gwa))
    std::cout << "XGetWindowAttributes failed" << std::endl;

  uint width = (uint) gwa.width;
  uint height = (uint) gwa.height;
  fprintf(stderr, "%d,%d", width, height);

  XImage
      *image =
      XGetImage(openDisplay, active, 0, 0, (unsigned int) width, (unsigned int) height, XAllPlanes(), ZPixmap);

  unsigned long red_mask = image->red_mask;
  unsigned long green_mask = image->green_mask;
  unsigned long blue_mask = image->blue_mask;

  pngwriter PNG(width, height, 0.0, file);
  uint x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      unsigned long pixel = XGetPixel (image, x, y);

      double blue = pixel & blue_mask;
      double green = (pixel & green_mask) >> 8;
      double red = (pixel & red_mask) >> 16;

      PNG.plot(x, height - y, red / 256.00, green / 256.00, blue / 256.00);
    }
  }
  PNG.close();
}

int GLWindow::GLScreenshot() {

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  fprintf(stderr, "%d,%d", width, height);

  const int pix = 3 * windowWidth * windowHeight;
  GLfloat *pixels = new GLfloat[pix];

  glReadBuffer(GL_FRONT);
  glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_FLOAT, pixels);
  pngwriter PNG(windowWidth, windowHeight, 0.0, "GLScreenshot.png");
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
      default:break;
    }
  }
  PNG.close();

  delete[] pixels;
}

void GLWindow::quit() {
  glfwSetWindowShouldClose(window, true);
}

void GLWindow::svgScreenshot(char *fileName) {
  if (graph) {
    svg::Dimensions *dimensions = new svg::Dimensions(windowWidth, windowHeight);
    svg::Document *doc = new svg::Document(fileName, svg::Layout(*dimensions, svg::Layout::BottomLeft));
    svg::SvgPrinter svg(doc, dimensions);
    svg.printGraph(graph, translateZ);

    delete dimensions;
    delete doc;
  }
}

void GLWindow::refresh() {
  refreshGraph->execute();
}
