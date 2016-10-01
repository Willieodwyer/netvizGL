//
// Created by werl on 19/09/16.
//

#ifndef NETVIZGL_SHADER_H
#define NETVIZGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/gl.h>


using namespace std;

class Shader {

public:
    GLuint Program;

    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

    virtual ~Shader();

    void Use();
};

#endif //NETVIZGL_SHADER_H
