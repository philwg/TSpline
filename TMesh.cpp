#include "TMesh.h"

using namespace std;
using namespace arma;


TMesh::TMesh(displayData* dD_ptr)
{
	this->dispData = dD_ptr;
}


TMesh::~TMesh()
{}


void TMesh::display()
{
	this->displayNodes();
	this->displayHorizontalEdges();
	this->displayVerticalEdges();
}


vector<float*> TMesh::get_Vertices()
{
	vector<float*> Vertices;
	for (int v=0; v < this->dispData->meshData->get_V_Height(); v++) {
		for (int h=0; h < this->dispData->meshData->get_H_Width(); h++) {
			Vertices.push_back(this->dispData->get_Vertex(h,v));
		}
	}
	return Vertices;
}


void TMesh::displayNodes()
{
	vector<float*> Vertices = this->get_Vertices();
	glColor3fv(this->dispData->Color[0]);
	glPointSize(this->dispData->ptSize[0]);
	glBegin(GL_POINTS);		
		for (vector<float*>::iterator Vertex=Vertices.begin(); Vertex!=Vertices.end(); Vertex++) {
			glVertex2fv(*Vertex);
		}
	glEnd();
}


void TMesh::displayHorizontalEdges()
{
	umat H_Edges = this->dispData->meshData->H_Edges;
	glColor3fv(this->dispData->Color[1]);
	glPointSize(this->dispData->ptSize[1]);	
	for (int v=0; v < H_Edges.n_rows; v++) {
		bool firstFound = false;
		int first_h = 0;
		int last_h = 0;
		for (int h=0; h < H_Edges.n_cols; h++) {
			if ((H_Edges[v,h]==1) && (!firstFound)) {
				first_h= h;
				firstFound = true;
			}
			bool endReached = ((h==H_Edges.n_cols-1) && (H_Edges[v,h]==1));
			if ((firstFound && (H_Edges[v,h]==0)) || (firstFound && endReached)) {
				last_h = h - (endReached? 0 : 1);
				glBegin(GL_POINTS);
					glVertex2fv(this->dispData->get_Vertex(first_h, v));
					glVertex2fv(this->dispData->get_Vertex(last_h, v));
				glEnd();
				glBegin(GL_LINES);
					glVertex2fv(this->dispData->get_Vertex(first_h, v));
					glVertex2fv(this->dispData->get_Vertex(last_h, v));
				glEnd();
				firstFound = false;
			}
		}
	}
}

void TMesh::displayVerticalEdges()
{
	umat V_Edges = this->dispData->meshData->V_Edges;
	glColor3fv(this->dispData->Color[1]);
	glPointSize(this->dispData->ptSize[1]);	
	glLineWidth(this->dispData->lnWidth);
	for (int h=0; h < V_Edges.n_cols; h++) {
		bool firstFound = false;
		int first_v = 0;
		int last_v = 0;
		for (int v=0; v < V_Edges.n_rows; v++) {
			if ((V_Edges[v,h]==1) && (!firstFound)) {
				first_v = v;
				firstFound = true;
			}
			bool endReached = ((v==V_Edges.n_rows-1) && (V_Edges[v,h]==1));
			if ((firstFound && (V_Edges[v,h]==0)) || (firstFound && endReached)) {
				last_v = v - (endReached? 0 : 1);
				glBegin(GL_POINTS);
					glVertex2fv(this->dispData->get_Vertex(h, first_v));
					glVertex2fv(this->dispData->get_Vertex(h, last_v));
				glEnd();
				glBegin(GL_LINES);
					glVertex2fv(this->dispData->get_Vertex(h, first_v));
					glVertex2fv(this->dispData->get_Vertex(h, last_v));
				glEnd();
				firstFound = false;
			}
		}
	}
}