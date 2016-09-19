//
// Created by werl on 16/09/16.
//

#include "point.h"

float Point::getX() const {
    return x;
}

void Point::setX(float x) {
    Point::x = x;
}

Point::Point() {}

Point::~Point() {

}

float Point::getY() const {
    return y;
}

void Point::setY(float y) {
    Point::y = y;
}

float Point::getZ() const {
    return z;
}

void Point::setZ(float z) {
    Point::z = z;
}
