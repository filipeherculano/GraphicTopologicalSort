#include "../include/ambient.h"

#include <iostream>

#include <GL/glut.h>

Ambient::Ambient(int stars, int radius) : stars_(stars), radius_(radius)
{
}

void Ambient::draw()
{
    draw_field(radius_);
    draw_sky(stars_);
}

void Ambient::draw_field(int radius)
{
    // TODO(filipe.herculano) : Create circular plane
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3i(radius, -6, radius);
    glVertex3i(-radius, -6, radius);
    glVertex3i(-radius, -6, -radius);
    glVertex3i(radius, -6, -radius);
    glEnd();
}

void Ambient::draw_sky(int stars)
{
    glColor3f(1.0, 1.0, 1.0);
    while (star_.size() < stars)
    {
        int x = (rand() % 300) - 150;
        int y = rand() % 150;
        int z = (rand() % 300) - 150;
        if (min(min(abs(x), abs(y)), abs(z)) >= 50)
            star_.push_back({x, {y, z}});
    }

    for (int i = 0; i < star_.size(); i++)
    {
        int x = star_[i].first;
        int y = star_[i].second.first;
        int z = star_[i].second.second;
        glTranslatef(x, y, z);
        glutSolidSphere(1, 10, 10);
        glTranslatef(-x, -y, -z);
    }
}