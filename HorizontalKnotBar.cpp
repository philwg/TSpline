#include "HorizontalKnotBar.h"

using namespace std;

HorizontalKnotBar::HorizontalKnotBar(displayData* dD_ptr)
{
	this->dispData = dD_ptr;
}

HorizontalKnotBar::~HorizontalKnotBar()
{}

void HorizontalKnotBar::display()
{
	vector<float*> Vertices = this->get_Vertices();
	glColor3fv(this->dispData->Color[2]);
	glPointSize(this->dispData->ptSize[2]);
	int index = 0;
	for (vector<float*>::iterator Vertex=Vertices.begin(); Vertex!=Vertices.end(); Vertex++) {
		char writeBuffer[4] = {'\0'};
		sprintf(writeBuffer, "%.1f", (this->dispData->meshData->get_H_KnotValues())(index++));
		this->renderBitmapString((*Vertex)[0]-9.0f, (*Vertex)[1]-24.0f, GLUT_BITMAP_HELVETICA_18, writeBuffer);
		glBegin(GL_POINTS);
			glVertex2fv(*Vertex);
		glEnd();
	}
	glLineWidth(this->dispData->lnWidth);
	glBegin(GL_LINES);
		glVertex2fv(Vertices.front());
		glVertex2fv(Vertices.back());
	glEnd();
}

vector<float*> HorizontalKnotBar::get_Vertices()
{
	vector<float*> Vertices;
	this->Y = 2.0f*this->dispData->get_VDelta()/3.0f;
	for (int h=0; h < this->dispData->meshData->H_Edges.n_cols; h++) {
		Vertices.push_back(new float[2] {this->dispData->get_VertX(h), this->Y});
	}
	return Vertices;
}