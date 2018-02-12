#include "Scene2DElement.h"

using namespace std;

Scene2DElement::Scene2DElement()
{}

Scene2DElement::Scene2DElement(displayData* dD_ptr)
{
	this->dispData = dD_ptr;
}

Scene2DElement::~Scene2DElement()
{}

void Scene2DElement::renderBitmapString(float x, float y, void *font, const char *string)
{
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

int Scene2DElement::getPickedIndex(int mState, int x, int y)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLuint selectedIndex;
	vector<float*> Points = this->get_Vertices(); 
	int vertexNb = Points.size();
	if ((mState == GLUT_DOWN) && (vertexNb > 0)) {				
		GLuint selectBuf[2 * vertexNb]; 					
		GLuint *pointeurBuffer_selected;	
		GLint selectedObjectNb; 							
		glSelectBuffer(2 * vertexNb, selectBuf);			
		glRenderMode(GL_SELECT); 							
		glPushMatrix();
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPickMatrix(x,
						  viewport[3] - y,
						  this->dispData->pickingPrecision,
						  this->dispData->pickingPrecision,
						  viewport); 
			glOrtho(0.0f,
					this->dispData->dispWdwWidth,
					0.0f,
					this->dispData->dispWdwHeight,
					this->dispData->zOrthoMin,
					this->dispData->zOrthoMax);
			glInitNames();
			glPushName(2);
			glColor3fv(this->dispData->Color[2]);
			for (int i=0; i<vertexNb; i++) {
				glLoadName(i);							
				glBegin(GL_POINTS);
					glVertex2fv(Points.at(i));
				glEnd();
			}
		glPopMatrix();
		glFlush();
		selectedObjectNb = glRenderMode(GL_RENDER); 
		if (selectedObjectNb) {
			pointeurBuffer_selected = (GLuint *)selectBuf; 
			pointeurBuffer_selected += 3;		
			selectedIndex = *pointeurBuffer_selected;
		}
		else selectedIndex = -1;
	}
	else selectedIndex = -1;
	//this->reshape(viewport[2], viewport[3]);
	return selectedIndex;
}