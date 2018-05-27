#include <GL/glut.h>

#include "include/graph.h"

#define ALTURA 700
#define LARGURA 700

double rotationY = 20.0;
double rotationX = 20.0;

double last_press_x = 0.0;
double last_press_y = 0.0;

Graph *G;

void Iluminacao()
{
	GLfloat luzAmbiente[4] = {0.0, 0.0, 0.0, 1.0};
	GLfloat luzDifusa[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat posicaoLuz[4] = {0.0, 50.0, -50.0, 1.0};

	GLfloat ka[4] = {0.0, 0.0, 1.0, 1.0};	 /* Reflete porcentagens da cor ambiente */
	GLfloat kd[4] = {0.0, 0.0, 0.46, 1.0};	/* Reflete porcentagens da cor difusa */
	GLfloat ks[4] = {0.03, 0.33, 0.98, 0.93}; /* Reflete porcentagens da cor especular */
	GLfloat ke[4] = {0.29, 0.0, 0.26, 0.01};
	GLfloat shininess = 40.0;

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ke);
}

void Desenha()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, -100.0, /* eye  */
			  0.0, 0.0, 0.0,	/* look */
			  0.0, 1.0, 0.0);   /*  up  */

	glRotated(rotationY, -1.0, 0.0, 0.0);
	glRotated(rotationX, 0.0, -1.0, 0.0);

	Iluminacao();

	G->draw_vertex();
	G->draw_edges();

	glFlush();
}

void specialKeys(unsigned char key, int x, int y)
{
	if (key == 'N' || key == 'n')
	{
		G->destroy_node();
		Desenha();
	}
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		last_press_x = x;
		last_press_y = y;
	}
}

void Inicializa()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 10.0, -10.0);

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
	glutCreateWindow("WAR MAP");
	glutDisplayFunc(Desenha);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
	glutKeyboardFunc(specialKeys);
	G = new Graph(4, 3);
	G->topological_sort();
	Inicializa();
	//CriarMenu();
	glutMainLoop();
	return 0;
}
