//
// Created by werl on 15/11/16.
//

#ifndef NETVIZGL_MENU_H
#define NETVIZGL_MENU_H

#include <GL/glew.h>

class Menu {

 public:
  Menu(GLfloat X1, GLfloat Y1, GLfloat X2, GLfloat Y2);
  void draw();

  GLfloat X1,Y1,X2,Y2;
};

#endif //NETVIZGL_MENU_H
