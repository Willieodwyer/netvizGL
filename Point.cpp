//
// Created by werl on 23/09/16.
//

#include "Point.h"

Point::Point(float radius, unsigned int rings, unsigned int sectors) {

    float const R = (float) 1.0/(rings-1);
    float const S = (float) 1.0/(sectors-1);

    int r, s, vertIndex = 0;
    verts = new GLfloat[rings * sectors * 3];


    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
            float const y = (float) sin( -M_PI_2 + M_PI * r * R );
            float const x = (float) cos(2*M_PI * s * S) * (float) sin( M_PI * r * R );
            float const z = (float) sin(2*M_PI * s * S) * (float) sin( M_PI * r * R );

            verts[vertIndex++] = x * radius;
            verts[vertIndex++] = y * radius;
            verts[vertIndex++] = z * radius;
        }

    indices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = indices.begin();
    for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
        }
}

void Point::draw(GLfloat x, GLfloat y, GLfloat z) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x,y,z);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
    glPopMatrix();
}
