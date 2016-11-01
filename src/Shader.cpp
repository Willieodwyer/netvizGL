//
// Created by werl on 29/09/16.
//


#include <GL/glew.h>
#include "../inc/Shader.h"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath) {
  string vertexString;
  string fragmentString;

  fstream vertexFile;
  fstream fragmentFile;

  vertexFile.open(vertexPath);

  if (vertexFile.is_open()) {
    printf("OPEN");
  } else
    printf("NOT OPEN.- %s", vertexPath);

  fragmentFile.open(fragmentPath);
  stringstream vShaderStream, fShaderStream;

  vShaderStream << vertexFile.rdbuf();
  fShaderStream << fragmentFile.rdbuf();

  vertexFile.close();
  fragmentFile.close();

  vertexString = vShaderStream.str();
  fragmentString = fShaderStream.str();

  const GLchar *vShaderCode = vertexString.c_str();
  const GLchar *fShaderCode = fragmentString.c_str();

  // 2. Compile shaders
  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];
  // Vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // Print compile errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // Fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  // Print compile errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
  // Shader Program
  this->Program = glCreateProgram();
  glAttachShader(this->Program, vertex);
  glAttachShader(this->Program, fragment);
  glLinkProgram(this->Program);
  // Print linking errors if any
  glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  // Delete the shaders as they're linked into our program now and no longer necessery
  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

Shader::~Shader() {

}

// Uses the current shader
void Shader::Use() {
  glUseProgram(this->Program);
}