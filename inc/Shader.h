//
// Created by werl on 19/09/16.
//

#ifndef NETVIZGL_SHADER_H
#define NETVIZGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

using namespace std;

class Shader {

public:
    GLuint Program;

    // Constructor generates the shader on the fly
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

    virtual ~Shader();

    // Uses the current shader
    void Use();
};

#endif //NETVIZGL_SHADER_H
