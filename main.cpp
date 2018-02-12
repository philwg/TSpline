#include <iostream>
#include "Data.h"
#include "displayData.h"
#include "Scene2D.h"

using namespace std;

Data* MeshData;
displayData* OpenGLData;
Scene2D* Mesh2D;

void display();
void initMenu();
void menu(int item);
void keyboard(unsigned char touche, int x, int y);
void special(int key, int x, int y);
void mouse(int mButton, int mState, int x, int y);
void mousemotion(int x, int y);		
void reshape(int width, int height);

void initMenu()
{
	int sm_hk = glutCreateMenu(menu);
	glutAddMenuEntry(" Horizontal Knots ",  0);
	glutAddMenuEntry(" ________________ ",  0);
	glutAddMenuEntry("   Move           ", 11);
	glutAddMenuEntry("   Insert         ", 12);
	glutAddMenuEntry("   Delete         ", 13);

	int sm_vk = glutCreateMenu(menu);
	glutAddMenuEntry("  Vertical Knots  ",  0);
	glutAddMenuEntry(" ________________ ",  0);
	glutAddMenuEntry("   Move           ", 21);
	glutAddMenuEntry("   Insert         ", 22);
	glutAddMenuEntry("   Delete         ", 23);

	int main_menu = glutCreateMenu(menu);
	glutAddSubMenu	("   Horiz. Knots   ", sm_hk);
	glutAddSubMenu  ("   Vert.  Knots   ", sm_vk);
	glutAddMenuEntry(" ________________ ",  0);
	glutAddMenuEntry("   CANCEL         ",  8);
	glutAddMenuEntry("   EXIT           ",  9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int item)
{
	Mesh2D->menu(item);
}

void display()
{
	Mesh2D->display();
}

void keyboard(unsigned char touche, int x, int y)
{
	Mesh2D->keyboard(touche, x, y);
}

void special(int key, int x, int y)
{
	Mesh2D->special(key, x, y);
}

void mouse(int mButton, int mState, int x, int y)
{
	Mesh2D->mouse(mButton, mState, x, y);
}

void mousemotion(int x, int y)
{
	Mesh2D->mousemotion(x, y);
}

void reshape(int width, int height)
{
	Mesh2D->reshape(width, height);
}


/*********************************************************/
/*             	Lancement de l'application				 */
/*********************************************************/

int main(int argc, char** argv)
{
	MeshData = new Data();
	OpenGLData = new displayData(MeshData);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(OpenGLData->dispWdwXpos, OpenGLData->dispWdwYpos);
	glutInitWindowSize(OpenGLData->dispWdwWidth, OpenGLData->dispWdwHeight);
	glutCreateWindow("T-Mesh");
		
	/* Initialisation des styles */
	glClearColor(OpenGLData->bgColor[0], OpenGLData->bgColor[1], OpenGLData->bgColor[2], OpenGLData->bgColor[3]);
	glEnable(GL_DEPTH_TEST);
	
	Mesh2D = new Scene2D(OpenGLData);
	
	/* Enregistrement des fonctions de rappel */
	initMenu();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemotion);

	Mesh2D->showScene();
	glutMainLoop();

	delete Mesh2D;
	delete OpenGLData;
	delete MeshData;

	return 0;
}