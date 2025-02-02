// 370FinalProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BasicShape.h"
#include <math.h>

GLuint g_ground;
GLuint g_box;
GLuint g_sphere;
GLuint g_pyramid;
GLuint g_cylinder;
GLuint g_wall;


#define K_MAT_RED   0
#define K_MAT_GREEN 1
#define K_MAT_BLUE  2
#define K_MAT_YELLOW 3
#define K_MAT_PINK  4
#define K_MAT_WHITE 10
#define K_MAT_BLACK 5

#define  DIS_CAM_TO_MODE 20
#define  GROUND_SIZE 500
#define  WALL_SIZE 120

GLuint g_texture;
char texture_file[100] = { "Texture/tiles.bmp" };
GLuint floor_texture;
char floor_file[100] = { "Texture/floor1.bmp" };
GLuint teapot_texture;
char teapot_file[100] = { "Texture/seamless.bmp" };
GLuint wall_texture;
char wall_file[100] = { "Texture/wall4.bmp" };


float g_x = 0.0;
float g_z = 30.0;
float lx = 0.0;
float lz = -1.0;

float g_x_origin = 0.0;
float g_angle = 0.0;

bool g_is_rotate = false;

float detal_moving = 0.0;
float detal_angle = 0.0;

void CalculateMoving(float val_moving);
void CalculateRot(float val_angle);

GLuint elephant;
float elephantrot;
float spin;
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
	int ret = false;
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
		ret = false;
		if (texture_image)
		{
			if (texture_image->data)
				free(texture_image->data);
			free(texture_image);
		}
	}
	return ret;
}

void loadObj(const char *fname)
{
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	elephant = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}
	glPointSize(2.0);
	glNewList(elephant, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);
}


void drawObj()
{
	glPushMatrix();
	//glTranslatef(0.0, 8.0,0.0);
	glScalef(2, 2, 2);
	glRotatef(elephantrot, 0, 1, 0);
	glCallList(elephant);
	glPopMatrix();
	elephantrot = elephantrot + 0.5;
	if (elephantrot>360)elephantrot = elephantrot - 360;
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
	case K_MAT_RED:
	{
		ambien[0] = 1.0f;
		diff_use[0] = 1.0f;
	}
	break;
	case K_MAT_GREEN:
	{
		ambien[1] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case K_MAT_BLUE:
	{
		ambien[2] = 1.0f;
		diff_use[2] = 1.0f;
	}
	break;
	case K_MAT_YELLOW:
	{
		ambien[0] = 1.0f;
		ambien[1] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case K_MAT_PINK:
	{
		ambien[0] = 1.0f;
		ambien[2] = 1.0f;
		diff_use[0] = 1.0f;
		diff_use[1] = 1.0f;
	}
	break;
	case K_MAT_BLACK:
	{
		ambien[0] = 0.0f;
		ambien[2] = 0.0f;
		diff_use[0] = 0.0f;
		diff_use[1] = 0.0f;
	}
	break;
	case K_MAT_WHITE:
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
		SetMaterialColor(K_MAT_WHITE);
		glCallList(g_box);

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
		glTranslatef(i * 50, 5.5, j * 50);
		glBindTexture(GL_TEXTURE_2D, boxText);
		SetMaterialColor(K_MAT_WHITE);
		glCallList(g_box);

		glPushMatrix();
			glTranslatef(0.0, 8.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, teapotText); //teapot texture
			SetMaterialColor(K_MAT_WHITE);
			glutSolidTeapot(5.0);
		glPopMatrix();

	glPopMatrix();
}

void DrawSpecialTeapot(const int &i, const int &j, GLuint &boxText, GLuint &teapotText) {
	glPushMatrix();
		glTranslatef(i * 50, 5.5, j * 50);		
		glBindTexture(GL_TEXTURE_2D, boxText);
		SetMaterialColor(K_MAT_WHITE);
		glCallList(g_box);

		glPushMatrix();
			glTranslatef(0.0, 8.5, 0.0);
			glRotatef(spin, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, teapotText); //teapot texture
			SetMaterialColor(K_MAT_WHITE);
			glutSolidTeapot(5.0);
			spin = spin + 0.1;
			if (spin>360)spin = spin - 360;
		glPopMatrix();
	glPopMatrix();
	
}

void RenderScene()
{
	if (detal_moving != 0.0)
		CalculateMoving(detal_moving);

	if (detal_angle != 0.0)
		CalculateRot(detal_angle);

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
	SetMaterialColor(K_MAT_WHITE);
	glCallList(g_ground);
	glPopMatrix();


	//Render Cube
	for (int i = -2; i < 3; i++)
	{
		for (int j = -2; j < 0; j++)
		{

			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);						


			glPushMatrix();
			glTranslatef(0.0, 11.0, 0.0);
			glColor4f(1.0, 1, 1, 0.1);
			glScalef(1, 1, 1);
			glutSolidCube(20.0);
			glPopMatrix();

			glDisable(GL_BLEND);
			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);

			DrawSpecialTeapot(0, 0, g_texture, teapot_texture);
			DrawBoxTeapot(i, j, g_texture, K_MAT_RED);
		}

		for (int j = 1; j < 3; j++)
		{
			DrawBoxTeapot_Texture(i, j, g_texture, teapot_texture);
		}
	}

	//Walls
	glNormal3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	SetMaterialColor(K_MAT_WHITE);
	glCallList(g_wall);
	glPopMatrix();

	//Render obj
	SetMaterialColor(K_MAT_YELLOW);
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
		detal_moving = 1.0;
		break;
	}
	case GLUT_KEY_DOWN:
	{
		detal_moving = -1.0;
		break;
	}
	case GLUT_KEY_LEFT:
	{
		detal_angle = -0.01;
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		detal_angle = 0.01;
		break;
	}
	default:
		break;
	}
}

void CalculateMoving(float value_moving)
{
	g_x += detal_moving * lx;
	g_z += detal_moving * lz;
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
		detal_moving = 0.0f;
		break;
	}
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
	{
		detal_angle = 0.0;
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
	LoadGLTextures(texture_file, &g_texture);							///TEXTURE
	LoadGLTextures(floor_file, &floor_texture);
	LoadGLTextures(teapot_file, &teapot_texture);
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

	g_box = BasicShape::MakeCube(5.0);


	g_x = DIS_CAM_TO_MODE * sin(g_angle);
	g_z = DIS_CAM_TO_MODE * cos(g_angle);

	g_ground = BasicShape::MakeGround(GROUND_SIZE, GROUND_SIZE, 0.5);
	g_wall = BasicShape::MakeWall(WALL_SIZE);

}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Museum - Final Project 370");

	Init();
	glutReshapeFunc(ReShape);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(OnKeyDown);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyDown);
	glutSpecialUpFunc(OnSpecialKeyUp);
	loadObj("robot.obj");
	glutMainLoop();

}

