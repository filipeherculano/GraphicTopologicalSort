#include "../include/building.h"

#include <GL/glut.h>

Building::Building(int x, int y, int z, int side, int height)
    : x_(x), y_(y), z_(z), side_(side), height_(height), is_destroyed_(false)
{
}

void Building::draw()
{
    // TODO we are missing windows!

    if(!is_destroyed_) glColor3f(0.8, 0.8, 0.8);
    else if (is_destroyed_ && y_ > -12){
        y_--;
        glColor3f(1.0 , 0.8 + ((double) y_ * 0.05), 0.8 + ((double) y_ * 0.05));
    } else if (is_destroyed_ && y_ <= -12)
        return;
    
    glTranslatef(x_, y_, z_);
    glutSolidCube(side_);
    glTranslatef(-x_, -y_, -z_);
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
