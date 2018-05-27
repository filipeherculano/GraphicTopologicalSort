#include "../include/building.h"

#include <GL/glut.h>

Building::Building(int x, int y, int z, int side, int height)
    : x_(x), y_(y), z_(z), side_(side), height_(height), is_destroyed_(false)
{
}

void Building::draw()
{
    // TODO we are missing windows!

    if (is_destroyed_)
        return;

    // front
    glBegin(GL_QUADS);
    glVertex3i(x_ + (side_ / 2), y_, z_ - (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_, z_ - (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_ + height_, z_ - (side_ / 2));
    glVertex3i(x_ + (side_ / 2), y_ + height_, z_ - (side_ / 2));
    glEnd();

    // back
    glBegin(GL_QUADS);
    glVertex3i(x_ + (side_ / 2), y_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_ + height_, z_ + (side_ / 2));
    glVertex3i(x_ + (side_ / 2), y_ + height_, z_ + (side_ / 2));
    glEnd();

    // left
    glBegin(GL_QUADS);
    glVertex3i(x_ - (side_ / 2), y_, z_ - (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_ + height_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_ + height_, z_ - (side_ / 2));
    glEnd();

    // right
    glBegin(GL_QUADS);
    glVertex3i(x_ + (side_ / 2), y_, z_ - (side_ / 2));
    glVertex3i(x_ + (side_ / 2), y_, z_ + (side_ / 2));
    glVertex3i(x_ + (side_ / 2), y_ + height_, z_ + (side_ / 2));
    glVertex3i(x_ + (side_ / 2), y_ + height_, z_ - (side_ / 2));
    glEnd();

    // bottom
    glBegin(GL_QUADS);
    glVertex3i(x_ + (side_ / 2), y_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_, z_ - (side_ / 2));
    glVertex3i(x_ + (side_ / 2), y_, z_ - (side_ / 2));
    glEnd();

    // top
    glBegin(GL_QUADS);
    glVertex3i(x_ + (side_ / 2), y_ + height_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_ + height_, z_ + (side_ / 2));
    glVertex3i(x_ - (side_ / 2), y_ + height_, z_ - (side_ / 2));
    glVertex3i(x_ + (side_ / 2), y_ + height_, z_ - (side_ / 2));
    glEnd();
}

int Building::x()
{
    return x_;
}

int Building::y()
{
    return y_;
}

int Building::z()
{
    return z_;
}

void Building::destroy()
{
    is_destroyed_ = true;
}