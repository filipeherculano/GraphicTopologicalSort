#include "include/graph.h"

#include <GL/glut.h>

#include <iostream>
#include <unistd.h>
#include <math.h>

#define ALTURA 700
#define LARGURA 700

double rotationY = 20.0;
double rotationX = 20.0;

double last_press_x = 0.0;
double last_press_y = 0.0;

double scale_x = 1;
double scale_y = 1;
double scale_z = 1;

const float DEG2RAD = 3.14159 / 180;
const double radius = 200.0;

Graph *G;

void Iluminacao()
{
	GLfloat luzAmbiente[4] = {0.0, 0.0, 0.0, 1.0};
	GLfloat luzDifusa[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4] = {50.0, 50.0, 50.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	GLfloat ka[4] = {0.11, 0.06, 0.11, 1.0}; /* Reflete porcentagens da cor ambiente */
	GLfloat kd[4] = {0.43, 0.47, 0.54, 1.0}; /* Reflete porcentagens da cor difusa */
	GLfloat ks[4] = {0.33, 0.33, 0.52, 1.0}; /* Reflete porcentagens da cor especular */
	GLfloat ke[4] = {0.0, 0.0, 0.0, 0.0};
	GLfloat shininess = 5.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ke);

	glColor3f(1.0, 1.0, 0.4);
	glTranslatef(50.0, 50.0, 50.0);
	glutSolidSphere(3, 200, 200);
	glTranslatef(-50.0, -50.0, -50.0);
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 200.0, /* eye  */
			  0.0, 0.0, 0.0,   /* look */
			  0.0, 1.0, 0.0);  /*  up  */

	glRotated(rotationY, 1.0, 0.0, 0.0);
	glRotated(rotationX, 0.0, 1.0, 0.0);
	glScaled(scale_x, scale_y, scale_z);

	Iluminacao();

	G->draw_vertex();
	G->draw_edges();
	G->draw_plane();

	glFlush();
}

void specialKeys(unsigned char key, int x, int y)
{
	if (key == 'N' || key == 'n')
	{
		G->destroy_node();
		for (int i = 0; i < 12; i++)
		{
			Draw();
			usleep(80000);
		}
	}
	else if (key == 'W' || key == 'w')
	{
		scale_x += 0.1;
		scale_y += 0.1;
		scale_z += 0.1;
	}
	else if (key == 'S' || key == 's')
	{
		scale_x -= 0.1;
		scale_y -= 0.1;
		scale_z -= 0.1;
	}
	glutPostRedisplay();
}

void Mouse_Motion(int x, int y)
{
	rotationX += (double)(x - last_press_x);
	rotationY += (double)(y - last_press_y);

	last_press_x = x;
	last_press_y = y;

	glutPostRedisplay();
}

void Mouse_Press(int button, int state, int x, int y)
{
	// TODO
}

void Inicializa()
{
	glClearColor(0.0f, 0.0f, 0.13f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 100.0, -100.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glShadeModel(GL_SMOOTH);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(LARGURA, ALTURA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("WAR MAP - Graphic Topological Sort");
	glutDisplayFunc(Draw);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
	//glutMouseWheelFunc();
	glutKeyboardFunc(specialKeys);
	G = new Graph(4, 3);
	G->topological_sort();
	Inicializa();
	//CriarMenu();
	glutMainLoop();
	return 0;
}
