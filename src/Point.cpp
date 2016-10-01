//
// Created by werl on 23/09/16.
//

#include "../inc/Point.h"

Point::Point(float radius, unsigned int rings, unsigned int sectors, float offsetX, float offsetY, float offsetZ) {
    const GLfloat RINGS = (float) 1.0 / (rings - 1);
    const GLfloat SECTORS = (float) 1.0 / (sectors - 1);

    int r, s, vertIndex = 0;
    indIndex = 0;

    vertices = new GLdouble[rings * sectors * 3];
    for (r = 0; r < rings; r++) {
        for (s = 0; s < sectors; s++) {

            GLdouble x = offsetX + cos(2 * M_PI * s * SECTORS) * (GLfloat) sin(M_PI * r * RINGS);
            GLdouble y = offsetY + sin(-M_PI_2 + M_PI * r * RINGS);
            GLdouble z = offsetZ + sin(2 * M_PI * s * SECTORS) * (GLfloat) sin(M_PI * r * RINGS);

            vertices[vertIndex++] = x * radius;
            vertices[vertIndex++] = y * radius;
            vertices[vertIndex++] = z * radius;
        }
    }

    indices = new GLuint[rings * sectors * 4];

    for (r = 0; r < rings - 1; r++)
        for (s = 0; s < sectors - 1; s++) {

            indices[indIndex++] = r * sectors + s;
            indices[indIndex++] = r * sectors + (s + 1);
            indices[indIndex++] = (r + 1) * sectors + (s + 1);
            indices[indIndex++] = (r + 1) * sectors + s;

        }
}

void Point::draw() {

    glVertexPointer(3, GL_DOUBLE, 0, this->vertices);
    glDrawElements(GL_QUADS, this->indIndex, GL_UNSIGNED_INT, this->indices);

}

Point::~Point() {
    delete vertices;
}
