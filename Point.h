//
// Created by werl on 16/09/16.
//

#ifndef NETVIZGL_POINT_H
#define NETVIZGL_POINT_H

class Point {

private:
    float x;
    float y;
    float z;

public:
    Point();
    ~Point();

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);


};


#endif //NETVIZGL_POINT_H
