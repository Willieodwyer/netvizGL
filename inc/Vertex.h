//
// Created by werl on 23/09/16.
//

#ifndef NETVIZGL_SPHERE_H
#define NETVIZGL_SPHERE_H

#include <cmath>
#include "Line.h"
#include <vector>
#include <mutex>
#include <FTGL/ftgl.h>

using namespace std;
class Vertex
{
public:
    Vertex(GLdouble offsetx, GLdouble offsety, GLdouble offsetz);
    virtual ~Vertex();

    static const unsigned int rings = 12, sectors = 12;
    static constexpr double radius = .01;

    vector<Vertex *> attachedPoints;
    void attachPoint(Vertex *p);

    vector<Line *> lines;

    GLdouble colourR;
    GLdouble colourG;
    GLdouble colourB;

    int degree;
    int level;

    volatile GLdouble posX, posY, posZ;
    volatile GLdouble force;
    volatile GLdouble forceX, forceY, forceZ;
    volatile GLdouble velocityX, velocityY, velocityZ;

    GLuint *indices;
    GLint indIndex;
    GLdouble *vertices;
    GLdouble *colours;
    std::mutex mtx;

    void setColour(GLdouble r, GLdouble g, GLdouble b);
    GLdouble *getColour();

    void drawPoints();
    void update();
    bool isPointerOver(double x, double y);
    double getDepth();
    void *getScreenPosition(GLdouble *pos);
    void drawText();

    FTPixmapFont *font;

    GLdouble *pos;
    char *text;

    void setText(const char *t);
};

#endif //NETVIZGL_SPHERE_H
