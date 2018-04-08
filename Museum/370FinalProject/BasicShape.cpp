
#include "stdafx.h"
#include "BasicShape.h"


BasicShape::BasicShape(void)
{

}


BasicShape::~BasicShape(void)
{

}

GLuint BasicShape::MakeSphere(const float& radius)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  glutSolidSphere(radius, 64, 64);
  glEndList();

  return dp_list;
}

GLuint BasicShape::MakeCylinder(const float& radius, const float& length)
{
  GLuint dp_list;
  dp_list = glGenLists(1);         
  glNewList(dp_list, GL_COMPILE);
  GLUquadricObj *quadratic_obj;
  quadratic_obj = gluNewQuadric();
  glRotatef(-90, 1.0, 0.0, 0.0);
  gluCylinder(quadratic_obj, radius, radius, length, 32, 32);
  glEndList();
  return dp_list;
}

GLuint BasicShape::MakeTruncatedCone(const float& base_rad, const float & top_rad, const float& length)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  GLUquadricObj *quadratic_obj;
  quadratic_obj = gluNewQuadric();
  gluCylinder(quadratic_obj, base_rad, top_rad, length, 32, 32);
  glEndList();

  return dp_list;
}

GLuint BasicShape::MakeCone(const float& base_rad, const float& length)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  GLUquadricObj *quadratic_obj;
  quadratic_obj = gluNewQuadric();
  gluCylinder(quadratic_obj, base_rad, 0.0, length, 32, 32);
  glEndList();

  return dp_list;
}

GLuint BasicShape::MakePyramid(const float& size, const float& height)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  double half_size = size*0.5;
  glBegin( GL_TRIANGLES );
  //Front face
  glNormal3f(0.0, 0.0, 1.0f);
  glVertex3f(0.0f, height, 0.0f);
  glVertex3f(-half_size, 0, half_size);
  glVertex3f(half_size, 0, half_size);

  //left face
  glNormal3f(-1.0, 0.0, 0.0f);
  glVertex3f(0.0, height, 0.0);
  glVertex3f(-half_size, 0.0, -half_size);
  glVertex3f(-half_size, 0.0, half_size);

  //back face
  glNormal3f(0.0, 0.0, -1.0f);
  glVertex3f(0.0f, height, 0.0f);
  glVertex3f(-half_size, 0, -half_size);
  glVertex3f(half_size, 0, -half_size);

  //Right face
  glNormal3f(1.0, 0.0, 0.0f);
  glVertex3f(0.0, height, 0.0);
  glVertex3f(half_size, 0.0, -half_size);
  glVertex3f(half_size, 0.0, half_size);
  glEnd();

  //Bottom face
  glBegin(GL_QUADS);
  glNormal3f(0.0, -1.0, 0.0f);
  glVertex3f(half_size, 0.0, half_size);
  glVertex3f(half_size, 0.0, -half_size);
  glVertex3f(-half_size, 0.0, -half_size);
  glVertex3f(-half_size, 0.0, half_size);
  glEnd();
  glEndList();

  return dp_list;

}

GLuint BasicShape::MakeFrustumShape(const float& bottom_size, const float& top_size, const float& height)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  double half_bottom_size = 0.5*bottom_size;
  double half_top_size = 0.5*top_size;

  glBegin(GL_QUADS);
  // Front Face
  glNormal3f(0.0, 0.0, 1.0);
  glVertex3f(-half_bottom_size, 0.0, half_bottom_size);
  glVertex3f(half_bottom_size, 0.0, half_bottom_size);
  glVertex3f(half_top_size, height, half_top_size);
  glVertex3f(-half_top_size, height, half_top_size);
  // Back Face
  glNormal3f(0.0, 0.0, -1.0);
  glVertex3f(-half_bottom_size, 0.0, -half_bottom_size);
  glVertex3f(half_bottom_size, 0.0, -half_bottom_size);
  glVertex3f(half_top_size, height, -half_top_size);
  glVertex3f(-half_top_size, height, -half_top_size);

  // Top Face
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(-half_top_size, height, -half_top_size);
  glVertex3f(-half_top_size, height, half_top_size);
  glVertex3f(half_top_size, height, half_top_size);
  glVertex3f(half_top_size, height, -half_top_size);
  // Bottom Face
  glNormal3f(0.0, -1.0, 0.0);
  glVertex3f(-half_bottom_size, 0.0, -half_bottom_size);
  glVertex3f( half_bottom_size, 0.0, -half_bottom_size);
  glVertex3f( half_bottom_size, 0.0, half_bottom_size);
  glVertex3f(-half_bottom_size, 0.0, half_bottom_size);
  // Right face
  glNormal3f(1.0, 0.0, 0.0);
  glVertex3f(half_bottom_size, 0.0, -half_bottom_size);
  glVertex3f(half_bottom_size, 0.0, half_bottom_size);
  glVertex3f(half_top_size, height, half_top_size);
  glVertex3f(half_top_size, height, -half_top_size);
  // Left Face
  glNormal3f(-1.0, 0.0, 0.0);
  glVertex3f(-half_bottom_size, 0.0, -half_bottom_size);
  glVertex3f(-half_bottom_size, 0.0, half_bottom_size);
  glVertex3f(-half_top_size, height, half_top_size);
  glVertex3f(-half_top_size, height, -half_top_size);
  glEnd();

  glEndList();

  return dp_list;
}

GLuint BasicShape::MakeOctagon(const float& side, const float& thickness)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  double anpha = P_PI/4.0;
  float x = sin(anpha) * side;
  float y = 0.5*side;

  float z = thickness;
  float center_to_mid_size = x + y;
  for (int j = 0; j < 8; j++) 
  {
    glPushMatrix();
    glTranslatef(-center_to_mid_size, 0.0, 0.0);
    //Draw 8 rectangle side
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, -y, z);
    glVertex3f(0.0, y, z);
    glVertex3f(0.0, y, 0);
    glVertex3f(0.0, -y, 0);
    glEnd();
    glPopMatrix();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, z);
    glVertex3f(-center_to_mid_size, -y, z);
    glVertex3f(-center_to_mid_size, y, z);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-center_to_mid_size, y, 0.0);
    glVertex3f(-center_to_mid_size, -y, 0.0);
    glEnd();

    glRotatef(45.0, 0.0, 0.0, 1.0);
  }

  glEndList();

  return dp_list;
}

GLuint BasicShape::MakeBox(const float length, const float width, const float height)
{
  GLuint dp_list;
  dp_list = glGenLists(1);
  glNewList(dp_list, GL_COMPILE);
  float x = length;
  float y = height;
  float z = width ;
  //front
  /*glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0, 0, z);
  glVertex3f(0, y, z);
  glVertex3f(x, y, z);
  glVertex3f(x, 0, z);
  glEnd();*/

  //Back
  /*glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, -1.0f);
  glVertex3f(0, 0, 0);
  glVertex3f(x, 0, 0);
  glVertex3f(x, y, 0);
  glVertex3f(0, y, 0);
  glEnd();

  // left
  glBegin(GL_QUADS);
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, z);
  glVertex3f(0, y, z);
  glVertex3f(0, y, 0);
  glEnd();*/

  //// right
  /*glBegin(GL_QUADS);
  glNormal3f(1.0f, 0.0f, 0.0f);
  glVertex3f(x, 0, z);
  glVertex3f(x, 0, 0);
  glVertex3f(x, y, 0);
  glVertex3f(x, y, z);
  glEnd();*/

  //Top
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(0, y, 0);
  glTexCoord2f(100.0f, 0.0f); glVertex3f(x, y, 0);
  glTexCoord2f(100.0f, 100.0f); glVertex3f(x, y, z);
  glTexCoord2f(0.0f, 100.0f); glVertex3f(0, y, z);

  //Bottom
  /*glBegin(GL_QUADS);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(0, 0, 0);
  glVertex3f(x, 0, 0);
  glVertex3f(x, 0, z);
  glVertex3f(0, 0, z);

  glEnd();*/

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

