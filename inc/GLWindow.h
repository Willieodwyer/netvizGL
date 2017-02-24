//
// Created by werl on 21/09/16.
//

#ifndef NETVIZGL_WINDOW_H
#define NETVIZGL_WINDOW_H

#include <GL/glew.h>
#include "Vertex.h"
#include "Widget.h"
#include "Command/Command.h"
#include "Graphs/Graph.h"
#include "Algorithms/Algorithm.h"
#include <GLFW/glfw3.h>
#include <pthread.h>
#include <thread>
#include <FTGL/ftgl.h>

class GLWindow {

 public:
  GLWindow(const int WIDTH, const int HEIGHT);

  static GLWindow *windowInstance;

  static GLWindow *Ins();

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
  bool mouseMIDDLE;
  bool mouseRIGHT;

  void render();

  void init();

  static void keyPressedEvent(GLFWwindow *window, int key, int scancode, int action, int mode);

  static void mousePressedEvent(GLFWwindow *window, int button, int action, int mods);

  static void mousePositionEvent(GLFWwindow *window, double xpos, double ypos);

  static void scrollEvent(GLFWwindow *window, double xoffset, double yoffset);
  std::thread *algorithmThread;
  std::thread *widgetThread;

  bool endThread = false;
  Graph *graph;

  Algorithm *algorithm;
  Command *loadGraph;

  char *graphFilePath;

  static void algorithmFunction();

  int GLScreenshot();

  bool screenShot;

  Widget *buttonWidget;

  static void widgetFunction(Widget *x);
  void quit();
  void X11Screenshot(char *file);

  Command *colourNode;
  FTPixmapFont *font;

  Command *textNode;
  bool takeSvgScreen = false;
  char *svgFileName;

  void svgScreenshot(char *fileName);
  void refresh();
  Command *refreshGraph;
  Command *dragNode;
  Command *updateGraph;
  Command *selectEdge;
  Vertex *selectedNode;
  int selectedVertexNumber = -1;
  bool keyCTRL = false;
  double mouseDiffX;
  double mouseDiffY;
  bool keySHIFT = false;
};

#endif //NETVIZGL_WINDOW_H
