//
// Created by werl on 21/09/16.
//

#ifndef NETVIZGL_WINDOW_H
#define NETVIZGL_WINDOW_H

#include "Vertex.h"
#include "Graph.h"
#include "SimpleForceDirected.h"
#include <GLFW/glfw3.h>

class Window {

 public:

  static Window *Instance();

  GLFWwindow *window;

  int windowWidth;
  int windowHeight;

  double pitch;
  double yaw;
  double bank;

  double translateX;
  double translateY;
  double translateZ;

  double mouseX;
  double mouseY;

  bool mouseLEFT;
  bool mouseRIGHT;

  void display();

  void GLInit();

  static void keyPressedEvent(GLFWwindow *window, int key, int scancode, int action, int mode);

  static void mousePressedEvent(GLFWwindow *window, int button, int action, int mods);

  static void mousePositionEvent(GLFWwindow *window, double xpos, double ypos);

  static void scrollEvent(GLFWwindow *window, double xoffset, double yoffset);

 private:

  Graph *graph;
  SimpleForceDirected *algorithm;

  Window(const int WIDTH, const int HEIGHT);

  static Window *windowInstance;
};

#endif //NETVIZGL_WINDOW_H
