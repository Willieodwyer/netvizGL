#include <GL/glew.h>
#include <iostream>
#include "../inc/Window.h"
#include "../inc/Graphs/AdjacencyGraph.h"
#include <glm/geometric.hpp>
#include <glm/gtx/transform.hpp>
//
// Created by werl on 21/09/16.
//
void Window::Update() {
  while (!Window::Instance()->endThread) {
    Window::Instance()->graph->update();
  }
}

void Window::Apply() {
  while (!Window::Instance()->endThread) {
    Window::Instance()->algorithm->apply();
  }
}

Window *Window::windowInstance = NULL;

class vec3;

Window *Window::Instance() {
  if (!windowInstance)   // Only allow one instance of class to be generated.
    windowInstance = new Window(1280, 720);
  return windowInstance;
}

Window::Window(const int WIDTH, const int HEIGHT) {

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

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //glEnable(GL_CULL_FACE);

  graph = new AdjacencyGraph("../Graphs/sirpenski5.txt");
  algorithm = new SimpleForceDirected(graph);

  updateThread = new thread(Update);
  applyThread = new thread(Apply);
}

void Window::display() {

  static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  static glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  static glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
  static glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  static glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
  static glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

  glm::mat4 view;
  view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                     glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(0.0f, 1.0f, 0.0f));

  while (!glfwWindowShouldClose(window)) {

    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    glClearColor(0.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluPerspective(45, (double) windowWidth / (double) windowHeight, .1, 100);

    glTranslatef(translateX, translateY, -translateZ);

    glRotatef(pitch, 1, 0, 0);   //pitch
    glRotatef(yaw, 0, 1, 0);     //yaw

    graph->draw();

    glLineWidth(4.0);

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
  window = glfwCreateWindow(windowWidth, windowHeight, "netvizGL", NULL, NULL);

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

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
    Window::Instance()->endThread = true;
    Window::Instance()->updateThread->join();
    Window::Instance()->applyThread->join();
  }

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


