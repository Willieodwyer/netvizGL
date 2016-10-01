//
// Created by werl on 29/09/16.
//

#include "../inc/line.h"

Line::Line(GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X2, GLfloat Y2, GLfloat Z2) {
    vertices = new GLdouble[6];
    vertices[0] = X1;
    vertices[1] = Y1;
    vertices[2] = Z1;
    vertices[3] = X2;
    vertices[4] = Y2;
    vertices[5] = Z2;
}

Line::~Line() {
    delete vertices;
}

void Line::draw() {
    glLineWidth(4.0);
    glVertexPointer(3, GL_DOUBLE, 0, this->vertices);
    glDrawArrays(GL_LINES, 0, 2);
    glLineWidth(1.0);

}
