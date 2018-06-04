#include "../include/building.h"

#include <GL/glut.h>

Building::Building(int x, int y, int z, int side, int height)
	: x_(x), y_(-12), z_(z), side_(side), height_(height), is_destroyed_(false), state_(DEAD)
{
}

void drawCube(GLuint _buildTextId){

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _buildTextId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 6.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glNormal3f(0.0, 1.0f, 0.0f);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f( 6.0f, 6.0f, -6.0f);
	  glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-6.0f, 6.0f, -6.0f);
	  glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-6.0f, 6.0f,  6.0f);
	  glTexCoord2f(0.0f, 1.0f);
      glVertex3f( 6.0f, 6.0f,  6.0f);
 
      // Bottom face (y = -6.0f)
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f( 6.0f, -6.0f,  6.0f);
	  glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-6.0f, -6.0f,  6.0f);
	  glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-6.0f, -6.0f, -6.0f);
	  glTexCoord2f(0.0f, 1.0f);
      glVertex3f( 6.0f, -6.0f, -6.0f);
 
      // Front face  (z = 6.0f)
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f( 6.0f,  6.0f, 6.0f);
	  glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-6.0f,  6.0f, 6.0f);
	  glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-6.0f, -6.0f, 6.0f);
	  glTexCoord2f(0.0f, 1.0f);
      glVertex3f( 6.0f, -6.0f, 6.0f);
 
      // Back face (z = -6.0f)
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f( 6.0f, -6.0f, -6.0f);
	  glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-6.0f, -6.0f, -6.0f);
	  glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-6.0f,  6.0f, -6.0f);
	  glTexCoord2f(0.0f, 1.0f);
      glVertex3f( 6.0f,  6.0f, -6.0f);
 
      // Left face (x = -6.0f)
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(-6.0f,  6.0f,  6.0f);
	  glTexCoord2f(1.0f, 0.0f);
      glVertex3f(-6.0f,  6.0f, -6.0f);
	  glTexCoord2f(1.0f, 1.0f);
      glVertex3f(-6.0f, -6.0f, -6.0f);
	  glTexCoord2f(0.0f, 1.0f);
      glVertex3f(-6.0f, -6.0f,  6.0f);
 
      // Right face (x = 6.0f)
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(6.0f,  6.0f, -6.0f);
	  glTexCoord2f(1.0f, 0.0f);
      glVertex3f(6.0f,  6.0f,  6.0f);
	  glTexCoord2f(1.0f, 1.0f);
      glVertex3f(6.0f, -6.0f,  6.0f);
	  glTexCoord2f(0.0f, 1.0f);
      glVertex3f(6.0f, -6.0f, -6.0f);
   glEnd();  // End of drawing color-cube
   glDisable(GL_TEXTURE_2D);
}

void Building::draw(GLuint _buildTextId)
{
	// TODO we are missing windows!
	update_state();

	switch (state_)
	{
	case BUILDING:
		y_++;
		glColor3f(0.3, 1.0 + ((double)y_ * 0.05), 0.3);
		glTranslatef(x_, y_, z_);
		//glutSolidCube(side_);

		drawCube(_buildTextId);


		glTranslatef(-x_, -y_, -z_);
		break;
	case ALIVE:
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(x_, y_, z_);
		drawCube(_buildTextId);
		glTranslatef(-x_, -y_, -z_);
		break;
	case DESTROYING:
		y_--;
		glColor3f(1.0, 0.8 + ((double)y_ * 0.05), 0.8 + ((double)y_ * 0.05));
		glTranslatef(x_, y_, z_);
		glutSolidCube(side_);
		glTranslatef(-x_, -y_, -z_);
		break;
	case DEAD:
		break;
	}
}

bool Building::built()
{
	return state_ == ALIVE;
}

void Building::start()
{
	state_ = BUILDING;
}

void Building::update_state()
{
	switch (state_)
	{
	case BUILDING:
		if (y_ == 0)
			state_ = ALIVE;
		break;
	case ALIVE:
		if (is_destroyed_)
			state_ = DESTROYING;
		break;
	case DESTROYING:
		if (y_ <= -12)
			state_ = DEAD;
		break;
	case DEAD:
		break;
	}
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

void Building::set_y(int y)
{
	y_ = y;
}
