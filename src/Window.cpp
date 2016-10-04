//
// Created by werl on 21/09/16.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include "../inc/Window.h"
#include "../inc/line.h"


Window::Window(const int WIDTH, const int HEIGHT) {

    this->windowWidth = WIDTH;
    this->windowHeight = HEIGHT;

    GLinit();

    point = new Point(.01, 6, 6, 10, 10, 0);
    point2 = new Point(.01, 6, 6, 0, 0, 0);
    point3 = new Point(.01, 6, 6, 10, 10, 10);
    point4 = new Point(.01, 6, 6, 30, -5, 10);
    line = new Line(0, 0, 0, .1, .1, .1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Window::display() {
    while (!glfwWindowShouldClose(window)) {

        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        glClearColor(0.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        gluPerspective(45, (double) windowWidth / (double) windowHeight, .1, 100);

        glTranslatef(0, 0, -1);

        glLineWidth(4.0);

        static float alpha = 0;

        glRotatef(alpha, 0, 1, 0);

        point->draw();
        point2->draw();
        point3->draw();
        point4->draw();
        line->draw();

        alpha += 1;


        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void Window::GLinit() {

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
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    }

    glfwSetKeyCallback(window, keyPressedEvent);
}

void Window::keyPressedEvent(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


