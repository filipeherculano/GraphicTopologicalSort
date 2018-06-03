#include "../include/edges.h"

#include <GL/glut.h>

Edges::Edges(Building source, Building destination)
    : source_(source), destination_(destination), is_destroyed_(true)
{
	source_.set_y(source_.y() + 12);
	destination_.set_y(destination_.y() + 12);
}

void Edges::draw()
{
    // TODO Decide the colors of the line
    if (is_destroyed_)
        return;

    glLineWidth(20.0);

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3i(source_.x(), source_.y(), source_.z());
    glColor3f(1.0, 0.0, 0.0);
    glVertex3i(destination_.x(), destination_.y(), destination_.z());
    glEnd();
}

bool Edges::is_source(Building s)
{
    return s.x() == source_.x() &&
           s.y() == source_.y() &&
           s.z() == source_.z();
}

void Edges::destroy()
{
    is_destroyed_ = true;
}

void Edges::start(){
	is_destroyed_ = false;	
}
