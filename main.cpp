#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

const GLuint WIDTH = 1280, HEIGHT = 720;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
// When a user presses the escape key, we set the WindowShouldClose property to true,
// closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 8);


    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "netvizGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetKeyCallback(window, key_callback);

    Shader shade("/home/werl/College/netvizGL/shaders/default.vert", "/home/werl/College/netvizGL/shaders/default.frag");


    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
            -0.4f, -0.5f, 0.0f, // Left
            0.4f, -0.5f, 0.0f, // Right
            0.0f,  0.5f, 0.0f  // Top
    };


    GLuint VAO;
    GLuint VB;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VB);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shade.Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;

}
