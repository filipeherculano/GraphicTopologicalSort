#include "include/graph.h"
#include "include/imageloader.h"

#include <GL/glut.h>

#include <iostream>
#include <unistd.h>
#include <math.h>

#define ALTURA 700
#define LARGURA 700

/* lighting variables - begin */

//angle of rotation
GLfloat angle = 0.0;

//diffuse light color variables
GLfloat dlr = 1.0;
GLfloat dlg = 1.0;
GLfloat dlb = 1.0;

//ambient light color variables
GLfloat alr = 1.0;
GLfloat alg = 1.0;
GLfloat alb = 1.0;

//light position variables
GLfloat lx = 0.0;
GLfloat ly = 0.0;
GLfloat lz = 1.0;
GLfloat lw = 0.0;

/* lighting variables - end */


double rotationY = 20.0;
double rotationX = 20.0;

double last_press_x = 0.0;
double last_press_y = 0.0;

double scale_x = 1;
double scale_y = 1;
double scale_z = 1;

Graph *G;

void mainMenu (int id);
void destroyNode(void);
void zoom(int id);
void moveLight(int id);
void zoomIn(void);
void zoomOut(void);

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _grassTextId, _bricksTextId; //The id of the texture

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

	GLfloat DiffuseLight[] = {dlr, dlg, dlb};
    GLfloat AmbientLight[] = {alr, alg, alb};
	glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight); //change the light accordingly
    glLightfv (GL_LIGHT1, GL_AMBIENT, AmbientLight); //change the light accordingly
    GLfloat LightPosition[] = {lx, ly, lz, lw}; //set the LightPosition to the specified values
    glLightfv (GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly
    gluLookAt (0.0, 0.0, 200.0, 
			0.0, 0.0, 0.0, 
			0.0, 1.0, 0.0);

	glRotated(rotationY, 1.0, 0.0, 0.0);
	glRotated(rotationX, 0.0, 1.0, 0.0);
	glScaled(scale_x, scale_y, scale_z);
	

	G->draw_vertex(_bricksTextId);
	G->draw_edges();
	G->draw_plane(_grassTextId);
	glutSwapBuffers();
    angle++; //increase the anglessss
}

void drawDfs(){
	G->next_node();
	for(int i = 0; i < 12; i++){
		Draw();
		usleep(80000);
	}
}

void specialKeys(unsigned char key, int x, int y) {

	switch(key) {
		case 'n':
			destroyNode();
			break;
		
		case 'w':
			zoomIn();
			break;

		case 's':
			zoomOut();
			break;
		
		case 'e':
			exit(0);
			break;
		
		case 'u':
			ly += 2.0;
			break;
		
		case 'j':
			ly -= 2.0;
			break;
		
		case 'k':
			lx += 2.0;
			break;
		
		case 'h':
			lx -= 2.0;
			break;
		
		case 'i':
			drawDfs();
			break;
		
		default:
			cout << "Acao nao encontrada!" << endl;
			break;
	}

	glutPostRedisplay();
}

void Mouse_Motion(int x, int y)
{
	rotationX += (double)(x - last_press_x);
	//rotationY += (double)(y - last_press_y);

	last_press_x = x;
	//last_press_y = y;

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

	Image* image1 = loadBMP("img/grass.bmp");
	_grassTextId = loadTexture(image1);
	delete image1;

	Image* buildText = loadBMP("img/wall.bmp");
	_bricksTextId = loadTexture(buildText);
	delete buildText;


	glShadeModel(GL_SMOOTH);
}

int main(int argc, char **argv) {

	int zoom_menu, lighting_menu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(LARGURA, ALTURA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("WAR MAP - Graphic Topological Sort");
	glutDisplayFunc(Draw);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
	glutKeyboardFunc(specialKeys);


	zoom_menu = glutCreateMenu(zoom);
		glutAddMenuEntry("Zoom In   (w)", 1);
		glutAddMenuEntry("Zoom Out  (s)", 2);

	lighting_menu = glutCreateMenu(moveLight);
		glutAddMenuEntry("Up     (u)", 1);
		glutAddMenuEntry("Down   (j)", 2);
		glutAddMenuEntry("Left   (h)", 3);
		glutAddMenuEntry("Right  (k)", 4);

	glutCreateMenu(mainMenu);
		glutAddMenuEntry("Insert Node   (i)", 0);
		glutAddMenuEntry("Remove Node       (n)", 1);
       	glutAddSubMenu("Zoom", zoom_menu);
		glutAddSubMenu("Lighting", lighting_menu);
       	glutAddMenuEntry("Exit", 4);
	glutAttachMenu (GLUT_RIGHT_BUTTON);

	G = new Graph(12, 14);
	G->topological_sort();

	Inicializa();
	glutMainLoop();
	return 0;
}

void destroyNode() {
	G->destroy_node();
	for (int i = 0; i < 12; i++)
	{
		Draw();
		usleep(80000);
	}
}

void zoomIn(void) {
	scale_x += 0.1;
    scale_y += 0.1;
	scale_z += 0.1;
	glutPostRedisplay();
}

void zoomOut(void) {
	scale_x -= 0.1;
    scale_y -= 0.1;
	scale_z -= 0.1;
	glutPostRedisplay();
}

/* main popup menu - actions */
void mainMenu (int id) {
    switch (id) {
		case 0:
			drawDfs();
			break;
		case 1:
			destroyNode();
			break;
		case 2:
			zoomIn();
			break;
		case 3:
			zoomOut();
			break;
		case 4:
			exit(0);
			break;
		default:
			break;
    }
}

void zoom(int id) {

	switch(id){
		case 1:
			zoomIn();
			break;
		case 2:
			zoomOut();
			break;
		default:
			break;
	}
}

void moveLight(int id) {
	switch(id){
		case 1:
			ly += 2.0;
			break;
		case 2:
			ly -= 2.0;
			break;
		case 3:
			lx -= 2.0;
			break;
		case 4:
			lx += 2.0;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}


