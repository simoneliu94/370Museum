
#include "stdafx.h"
#include "BasicShape.h"


BasicShape::BasicShape(void)
{

}


BasicShape::~BasicShape(void)
{

}


GLuint BasicShape::MakeGround(const float length, const float width, const float height)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  float x = length;
  float y = height;
  float z = width ;
  
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(0, y, 0);
  glTexCoord2f(100.0f, 0.0f); glVertex3f(x, y, 0);
  glTexCoord2f(100.0f, 100.0f); glVertex3f(x, y, z);
  glTexCoord2f(0.0f, 100.0f); glVertex3f(0, y, z);

  glEndList();

  return dp_list;
}


GLuint BasicShape::MakeWall(const float& size)
{
	GLuint dp_list;
	dp_list = glGenLists(1);
	glNewList(dp_list, GL_COMPILE);

	glBegin(GL_QUADS);        					//FRONT
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, 0, size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, 0, size);
	glEnd();

	glBegin(GL_QUADS);        					//BACK
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, -size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, 0, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, 0, -size);
	glEnd();

	glBegin(GL_QUADS);        					//RIGHT SIDE
	glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, 0, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, 0, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(size, size, -size);
	glEnd();

	glBegin(GL_QUADS);        					//LEFT SIDE
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, size, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, 0, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, 0, -size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, size, -size);
	glEnd();

	glEndList();
	return dp_list;
}

GLuint BasicShape::MakeCube(const float& size)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  glBegin(GL_QUADS);

  // Front Face
  glNormal3f(0.0f, 0.0, 1.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  size);
  // Back Face
  glNormal3f(0.0f, 0.0, -1.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);
  // Top Face
  glNormal3f(0.0f, 1.0, 0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);
  // Bottom Face
  glNormal3f(0.0f, -1.0, 0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( size, -size, -size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);
  // Right face
  glNormal3f(1.0f, 0.0, 0.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);
  // Left Face
  glNormal3f(-1.0f, 0.0, 0.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size,  size);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
  glEnd();

  glEndList();

  return dp_list;
}

