#include "../include/ambient.h"
#include <iostream>
#include <GL/glut.h>
 

Ambient::Ambient(int stars, int radius) : stars_(stars), radius_(radius)
{
}

void Ambient::draw(GLuint _textureId)
{
    draw_field(radius_, _textureId);
    draw_sky(stars_);
}

void Ambient::draw_field(int radius, GLuint _textureId) {

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3i(radius, -6, radius);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3i(-radius, -6, radius);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3i(-radius, -6, -radius);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3i(radius, -6, -radius);
    glEnd();

    glDisable(GL_TEXTURE_2D);
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