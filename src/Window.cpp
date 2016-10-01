//
// Created by werl on 21/09/16.
//
#include <GLFW/glfw3.h>
#include <cstdio>
#include <GL/glu.h>
#include <iostream>
#include "../inc/Window.h"
#include "../inc/line.h"


Window::Window(const int WIDTH, const int HEIGHT) {

    point = new Point(.1, 9, 9, 10, 10, 0);
    point2 = new Point(.8, 9, 9, 0, 0, 0);
    point3 = new Point(.1, 9, 9, 10, 10, 10);
    point4 = new Point(.1, 9, 9, 30, -5, 10);
    line = new Line(0, 0, 0, 1, 1, 1);


    this->windowWidth = WIDTH;
    this->windowHeight = HEIGHT;

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

    glfwSetWindowPos(window, 320, 180);

    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Window::display() {
    while (!glfwWindowShouldClose(window)) {

        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        glClearColor(0.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        gluPerspective(45, (double) windowWidth / (double) windowHeight, 0, 100);

        glMatrixMode(GL_MODELVIEW_MATRIX);
        glTranslatef(0, 0, -5);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glLineWidth(4.0);

        static float alpha = 0;

        glRotatef(alpha, 0, 1, 0);

        line->draw();
        point->draw();
        point2->draw();
        point3->draw();
        point4->draw();

        alpha += .1;


        // Update Screen
        glfwSwapBuffers(window);

        // Check for any input, or window movement
        glfwPollEvents();
    }
}


