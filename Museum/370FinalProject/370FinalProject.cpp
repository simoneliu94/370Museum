// 370FinalProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BasicShape.h"
#include <math.h>

GLuint GROUND;
GLuint BOX;
GLuint WALL;


#define M_RED   0
#define M_GREEN 1
#define M_BLUE  2
#define M_YELLOW 3
#define M_PINK  4
#define M_WHITE 10
#define M_BLACK 5

#define  DIS_CAMERA 20
#define  GROUND_SIZE 500
#define  WALL_SIZE 120

GLuint box_texture;
char box_file[100] = { "Texture/tiles.bmp" };
GLuint box_texture2;
char box_file2[100] = { "Texture/bubble.bmp" };

GLuint floor_texture;
char floor_file[100] = { "Texture/floor1.bmp" };

GLuint teapot_texture;
char teapot_file[100] = { "Texture/ring.bmp" };
GLuint teapot_texture2;
char teapot_file2[100] = { "Texture/book.bmp" };
GLuint teapot_texture3;
char teapot_file3[100] = { "Texture/cera.bmp" };
GLuint teapot_texture4;
char teapot_file4[100] = { "Texture/graffi.bmp" };
GLuint teapot_texture5;
char teapot_file5[100] = { "Texture/lace.bmp" };
GLuint teapot_texture6;
char teapot_file6[100] = { "Texture/flower.bmp" };
GLuint teapot_texture7;
char teapot_file7[100] = { "Texture/light.bmp" };
GLuint teapot_texture8;
char teapot_file8[100] = { "Texture/pixa.bmp" };
GLuint teapot_texture9;
char teapot_file9[100] = { "Texture/heart.bmp" };
GLuint teapot_texture10;
char teapot_file10[100] = { "Texture/pattern2.bmp" };
GLuint teapot_texture11;
char teapot_file11[100] = { "Texture/leaf.bmp" };
GLuint teapot_texture12;
char teapot_file12[100] = { "Texture/body3.bmp" };
GLuint teapot_texture13;
char teapot_file13[100] = { "Texture/hibiscus.bmp" };
GLuint teapot_texture14;
char teapot_file14[100] = { "Texture/coffee.bmp" };
GLuint teapot_texture15;
char teapot_file15[100] = { "Texture/pattern.bmp" };

GLuint wall_texture;
char wall_file[100] = { "Texture/wall4.bmp" };

float g_x = 0.0;
float g_z = 30.0;
float lx = 0.0;
float lz = -1.0;

float g_x_origin = 0.0;
float g_angle = 0.0;

bool g_is_rotate = false;

float delta_moving = 0.0;
float delta_angle = 0.0;

void CalculateMoving(float val_moving);
void CalculateRot(float val_angle);

float spin;
float spin2;
char ch = '1';

AUX_RGBImageRec *LoadBMP(char *Filename)
{
	FILE *File = NULL;

	if (!Filename)
		return NULL;
	fopen_s(&File, Filename, "r");
	if (File)
	{
		fclose(File);
		return auxDIBImageLoadA((LPCSTR)Filename);
	}
	return NULL;
}

bool LoadGLTextures(char *file, GLuint *texture)
{
	int boolean = false;
	AUX_RGBImageRec *texture_image = NULL;

	if (texture_image = LoadBMP(file))
	{
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture_image->sizeX, texture_image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_image->data);
	}
	else
	{
		boolean = false;
		if (texture_image)
		{
			if (texture_image->data)
				free(texture_image->data);
			free(texture_image);
		}
	}
	return boolean;
}


void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4])
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void SetMaterialColor(const int& type)
{
	GLfloat ambien[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diff_use[] = { 0.0, 0.0, 0.0, 1.0 };
	switch (type)
	{
	case M_RED:
	{
		ambien[0] = 1.0f;
		diff_use[0] = 1.0f;
	}
	break;
	case M_GREEN:
	{
		ambien[1] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case M_BLUE:
	{
		ambien[2] = 1.0f;
		diff_use[2] = 1.0f;
	}
	break;
	case M_YELLOW:
	{
		ambien[0] = 1.0f;
		ambien[1] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case M_PINK:
	{
		ambien[0] = 1.0f;
		ambien[2] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case M_BLACK:
	{
		ambien[0] = 0.0f;
		ambien[2] = 0.0f;
		diff_use[0] = 0.0f;
		diff_use[1] = 0.0f;
	}
	break;
	case M_WHITE:
	default:
	{
		ambien[0] = 1.0f;
		ambien[1] = 1.0f;
		ambien[2] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
		diff_use[2] = 1.0f;
	}
	break;
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambien);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void DrawCoordinate()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100.0);
	glEnd();

	glEnable(GL_LIGHTING);
}

void DrawBoxTeapot(const int &i, const int &j, GLuint &boxText, const int& type) {
	glPushMatrix();
		glTranslatef(i * 50, 5.5, j * 50);
		glBindTexture(GL_TEXTURE_2D, boxText);
		SetMaterialColor(M_WHITE);
		glCallList(BOX);

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			glTranslatef(0.0, 8.0, 0.0);
			SetMaterialColor(type);
			glutSolidTeapot(5.0);
			glPopMatrix();
		glEnable(GL_TEXTURE_2D);

	glPopMatrix();
}

void DrawBoxTeapot_Texture(const int &i, const int &j, GLuint &boxText, GLuint &teapotText) {
	glPushMatrix();
		glTranslatef(i, 5.5, j);
		glBindTexture(GL_TEXTURE_2D, boxText);
		SetMaterialColor(M_WHITE);
		glCallList(BOX);

		glPushMatrix();
			glTranslatef(0.0, 8.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, teapotText);
			SetMaterialColor(M_WHITE);
			glutSolidTeapot(5.0);
		glPopMatrix();

	glPopMatrix();
}

void SpinningTeapot(int x, int y, GLuint &boxText, GLuint &teapotText) {
	float speed = 0.05;
	glPushMatrix();
	glRotatef(spin2, 0.0, 1.0, 0.0);
	DrawBoxTeapot_Texture(x, y, boxText, teapotText);
	spin2 = spin2 + speed;
	if (spin2>360)spin = spin2 - 360;
	glPopMatrix();
}

void DrawSpecialTeapot(const int &i, const int &j, GLuint &boxText, GLuint &teapotText) {
	glPushMatrix();
	glScalef(2, 2, 2);
		glTranslatef(i * 50, 5.5, j * 50);		
		glBindTexture(GL_TEXTURE_2D, boxText);
		SetMaterialColor(M_WHITE);
		glCallList(BOX);

		glPushMatrix();
			glTranslatef(0.0, 8.5, 0.0);
			glRotatef(spin, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, teapotText); //teapot texture
			SetMaterialColor(M_WHITE);
			glutSolidTeapot(5.0);
			spin = spin + 0.05;
			if (spin>360)spin = spin - 360;
		glPopMatrix();
	glPopMatrix();	
}

void DisplayScene()
{
	if (delta_moving != 0.0)
		CalculateMoving(delta_moving);

	if (delta_angle != 0.0)
		CalculateRot(delta_angle);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(g_x, 10.0, g_z, g_x + lx, 10.0, g_z + lz, 0.0, 10.0, 0.0);

	//Render Coordinate 
	glPushMatrix();
	//DrawCoordinate();
	glPopMatrix();

	//Render Ground
	glPushMatrix();
	glTranslatef(-0.5*GROUND_SIZE, 0.0, -0.5*GROUND_SIZE);
	glBindTexture(GL_TEXTURE_2D, floor_texture);
	SetMaterialColor(M_WHITE);
	glCallList(GROUND);
	glPopMatrix();


	//Render Object
	for (int i = -2; i < 3; i++)
	{
		DrawSpecialTeapot(0, 0, box_texture2, teapot_texture9);
	}	

	DrawBoxTeapot_Texture(-2 * 50, -2 * 50, box_texture, teapot_texture8);
	DrawBoxTeapot_Texture(-1 * 50, -2 * 50, box_texture, teapot_texture11);
	DrawBoxTeapot_Texture(0 * 50, -2 * 50, box_texture, teapot_texture12);
	DrawBoxTeapot_Texture(1 * 50, -2 * 50, box_texture, teapot_texture14);
	DrawBoxTeapot_Texture(2 * 50, -2 * 50, box_texture, teapot_texture15);

	DrawBoxTeapot_Texture(-2 * 50, 2 * 50, box_texture, teapot_texture2);
	DrawBoxTeapot_Texture(-1 * 50, 2 * 50, box_texture, teapot_texture3);
	DrawBoxTeapot_Texture(0 * 50, 2 * 50, box_texture, teapot_texture4);
	DrawBoxTeapot_Texture(1 * 50, 2 * 50, box_texture, teapot_texture5);
	DrawBoxTeapot_Texture(2 * 50, 2 * 50, box_texture, teapot_texture);

	SpinningTeapot(0 * 50 + 40, 0, box_texture, teapot_texture6);
	SpinningTeapot(0 * 50 - 40, 0, box_texture, teapot_texture10);
	SpinningTeapot(0, 0 * 50 + 40, box_texture, teapot_texture7);
	SpinningTeapot(0, 0 * 50 - 40, box_texture, teapot_texture13);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(10, 0.2, 10);
	glColor3f(1, 0, 0);
	SetMaterialColor(M_RED);
	glutSolidCube(10.0);
	glPopMatrix();

	//Walls
	glNormal3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	SetMaterialColor(M_WHITE);
	glCallList(WALL);
	glPopMatrix();

	//Render obj
	SetMaterialColor(M_YELLOW);
	//drawObj();


	glFlush();
	glutPostRedisplay();
}

void ReShape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float)width / (float)height;
	gluPerspective(45.0, ratio, 1, 500.0);
	glMatrixMode(GL_MODELVIEW);
}


void OnSpecialKeyDown(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		delta_moving = 1.0;
		break;
	}
	case GLUT_KEY_DOWN:
	{
		delta_moving = -1.0;
		break;
	}
	case GLUT_KEY_LEFT:
	{
		delta_angle = -0.01;
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		delta_angle = 0.01;
		break;
	}
	default:
		break;
	}
}

void CalculateMoving(float value_moving)
{
	g_x += delta_moving * lx;
	g_z += delta_moving * lz;
}

void CalculateRot(float val_angle)
{
	g_angle += val_angle;

	lx = sin(g_angle);
	lz = -cos(g_angle);
}

void OnSpecialKeyUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
	case GLUT_KEY_UP:
	{
		delta_moving = 0.0f;
		break;
	}
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
	{
		delta_angle = 0.0;
		break;
	}
	default:
		break;
	}
}

void OnKeyDown(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'A':
	{
		int ret = 0;
		break;
	}
	case 'a':
	{
		int ret = 1;
		break;
	}
	default:
		break;
	}
}


void OnKeyUp(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'A':
	{
		int ret = 0;
		break;
	}
	case 'a':
	{
		int ret = 1;
		break;
	}
	default:
		break;
	}
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	LoadGLTextures(box_file, &box_texture);							///TEXTURE
	LoadGLTextures(box_file2, &box_texture2);
	
	LoadGLTextures(floor_file, &floor_texture);

	LoadGLTextures(teapot_file, &teapot_texture);
	LoadGLTextures(teapot_file2, &teapot_texture2);
	LoadGLTextures(teapot_file3, &teapot_texture3);
	LoadGLTextures(teapot_file4, &teapot_texture4);
	LoadGLTextures(teapot_file5, &teapot_texture5);
	LoadGLTextures(teapot_file6, &teapot_texture6);
	LoadGLTextures(teapot_file7, &teapot_texture7);
	LoadGLTextures(teapot_file8, &teapot_texture8);
	LoadGLTextures(teapot_file9, &teapot_texture9);
	LoadGLTextures(teapot_file10, &teapot_texture10);
	LoadGLTextures(teapot_file11, &teapot_texture11);
	LoadGLTextures(teapot_file12, &teapot_texture12);
	LoadGLTextures(teapot_file13, &teapot_texture13);
	LoadGLTextures(teapot_file14, &teapot_texture14);
	LoadGLTextures(teapot_file15, &teapot_texture15);

	LoadGLTextures(wall_file, &wall_texture);


	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	GLfloat diff_use[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	GLfloat shininess = 50.0f;
	glMateriali(GL_FRONT, GL_SHININESS, shininess);

	BOX = BasicShape::MakeCube(5.0);

	g_x = DIS_CAMERA * sin(g_angle);
	g_z = DIS_CAMERA * cos(g_angle);

	GROUND = BasicShape::MakeGround(GROUND_SIZE, GROUND_SIZE, 0.5);
	WALL = BasicShape::MakeWall(WALL_SIZE);

}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Museum - Final Project 370");

	Init();
	glutReshapeFunc(ReShape);
	glutDisplayFunc(DisplayScene);
	glutKeyboardFunc(OnKeyDown);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyDown);
	glutSpecialUpFunc(OnSpecialKeyUp);
	glutMainLoop();
}

