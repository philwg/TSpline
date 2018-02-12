#include "Scene2D.h"

using namespace std;
using namespace arma;


Scene2D::Scene2D(displayData* dD_ptr)
{
	this->dispData = dD_ptr;
	
	/* Initialisation des élements à afficher */
	this->HK_Bar = new HorizontalKnotBar(this->dispData);
	this->VK_Bar = new VerticalKnotBar(this->dispData);
	this->T_Grid = new TMesh(this->dispData);
	//this->Anchors = AnchorSet(this->dispData);
	
	this->action = 0;
	this->selected = -1;
	this->A_selected = -1;
}

Scene2D::~Scene2D()
{
	delete this->HK_Bar;
	delete this->VK_Bar;
	delete this->T_Grid;
}

void Scene2D::showScene()
{
	glutPostRedisplay();
}

void Scene2D::menu(int item)
{
	switch (item) {
	
		case 11:			//--------------------- Modifier un noeud horizontal
			this->action = item;

			glutSetCursor(GLUT_CURSOR_INFO);
			break;
			
		case 12:			//--------------------- Insérer un noeud horizontal
			this->action = item;

			glutSetCursor(GLUT_CURSOR_HELP);
			break;
			
		case 13:			//--------------------- Supprimer un noeud horizontal
			this->action = item;

			glutSetCursor(GLUT_CURSOR_DESTROY);
			break;
			
		case 21:			//--------------------- Modifier un noeud vertical
			this->action = item;

			glutSetCursor(GLUT_CURSOR_INFO);
			break;
			
		case 22:			//--------------------- Insérer un noeud vertical
			this->action = item;

			glutSetCursor(GLUT_CURSOR_HELP);
			break;
			
		case 23:			//--------------------- Supprimer un noeud vertical
			this->action = item;

			glutSetCursor(GLUT_CURSOR_DESTROY);
			break;
			
		case 8:				//--------------------- Annuler les opérations en cours
			this->action = 0;
			this->selected = -1;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			glutPostRedisplay();
			break;
			
		case 9:				//-------------------- Quitter
			exit(0);
			break;		
	}
}

void Scene2D::keyboard(unsigned char touche, int x, int y)
{
	switch(touche) {
	
		case 'H':
			if (this->dispData->meshData->get_H_degree() < this->dispData->meshData->get_H_Width()-2) {
				this->dispData->meshData->change_H_degree(1);
				glutPostRedisplay();			
			}
			break;
			
		case 'h':
			if (this->dispData->meshData->get_H_degree() > 1) {
				this->dispData->meshData->change_H_degree(-1);
				glutPostRedisplay();
			}
			break;
			
		case 'V':
			if (this->dispData->meshData->get_V_degree() < this->dispData->meshData->get_V_Height()-2) {
				this->dispData->meshData->change_V_degree(1);
				glutPostRedisplay();			
			}
			break;	
			
		case 'v':
			if (this->dispData->meshData->get_V_degree() > 1) {
				this->dispData->meshData->change_V_degree(-1);
				glutPostRedisplay();
			}
			break;
			
		case 'q':
			exit(0);
			break;
	}	
}

void Scene2D::special(int key, int x, int y)
{
	switch(key) {
	
		case GLUT_KEY_LEFT:
			if (this->A_selected >= 0) {
				this->A_selected--;
				glutPostRedisplay();
			}
			break;
			
		case GLUT_KEY_RIGHT:
			if (this->A_selected < 10) { 	//}this->Anchors.size()) {
				this->A_selected++;
				glutPostRedisplay();
			}
			break;
			
		default :
			break;
	}	
}

void Scene2D::mouse(int mButton, int mState, int x, int y)
{
	if (mButton == GLUT_LEFT_BUTTON) {

		int H_size = this->dispData->meshData->get_H_Width();
		int V_size = this->dispData->meshData->get_V_Height();
		urowvec new_VertNode_row(H_size);
		uvec    new_HoriNode_col(V_size);
		vec HKI(H_size + 1);
		vec VKI(V_size + 1);
		float new_KI;
				
		switch (action) {

			case 11:			//------------------------- On modifie un noeud horizontal
				this->selected = this->HK_Bar->getPickedIndex(mState, x, y);
				break;

			case 12:			//------------------------- On insère un noeud horizontal
				this->selected = this->HK_Bar->getPickedIndex(mState, x, y);
				if (this->selected > 0) {
					new_HoriNode_col.fill(0);
					this->dispData->meshData->V_Edges.insert_cols(this->selected, new_HoriNode_col);
					for(int v=0; v < V_size; v++) {
						if	  ((this->dispData->meshData->H_Edges(v,this->selected-1)==1)
							&& (this->dispData->meshData->H_Edges(v,this->selected)==1)) new_HoriNode_col(v) = 1;
						else new_HoriNode_col(v) = 0;
					}
					this->dispData->meshData->H_Edges.insert_cols(this->selected, new_HoriNode_col);
					new_KI = this->dispData->meshData->H_Knot_Intervals(this->selected)/2.0f;
					HKI(span(0, this->selected-1))
						= this->dispData->meshData->H_Knot_Intervals.head(this->selected);
					HKI(this->selected) = new_KI;
					HKI(this->selected+1) = new_KI;
					HKI(span(this->selected+2, H_size))
						= this->dispData->meshData->H_Knot_Intervals.tail(H_size - this->selected - 1);
					this->dispData->meshData->H_Knot_Intervals = HKI;
					glutPostRedisplay();
				}
				break;
				
			case 13:			//------------------------- On supprime un noeud horizontal
				this->selected = this->HK_Bar->getPickedIndex(mState, x, y);
				
				break;

								
			case 21:			//------------------------- On modifie un noeud vertical
				this->selected = this->VK_Bar->getPickedIndex(mState, x, y);
				
				break;
				
			case 22:			//------------------------- On insère un noeud vertical
				this->selected = this->VK_Bar->getPickedIndex(mState, x, y);
				if (this->selected > 0) {
					new_VertNode_row.fill(0);
					this->dispData->meshData->H_Edges.insert_rows(this->selected, new_VertNode_row);
					for (int h=0; h < H_size; h++) {
						if    ((this->dispData->meshData->V_Edges(this->selected-1,h)==1)
							&& (this->dispData->meshData->V_Edges(this->selected,h)==1)) new_VertNode_row(h) = 1;
						else new_VertNode_row(h) = 0;
					}
					this->dispData->meshData->V_Edges.insert_rows(this->selected, new_VertNode_row);
					new_KI = this->dispData->meshData->V_Knot_Intervals(this->selected)/2.0f;
					VKI(span(0, this->selected-1))
						= this->dispData->meshData->V_Knot_Intervals.head(this->selected);
					VKI(this->selected) = new_KI;
					VKI(this->selected+1) = new_KI;
					VKI(span(this->selected+2, V_size))
						= this->dispData->meshData->V_Knot_Intervals.tail(V_size - this->selected - 1);
					this->dispData->meshData->V_Knot_Intervals = VKI;
					glutPostRedisplay();
				}
				break;
			
			default:
				break;		
		}
		if (mState == GLUT_UP) this->selected = -1;		
	}
}

void Scene2D::mousemotion(int x, int y)
{
	if (this->selected != -1) {
	
		float new_x = (float)x;
		float new_y = (float)(this->dispData->dispWdwHeight - y);
		
		if (action == 11) { 
			if (new_x < this->dispData->get_VertX(selected-1)) new_x = this->dispData->get_VertX(selected-1)+12.0f;
			else if (new_x > this->dispData->get_VertX(selected+1)) new_x = this->dispData->get_VertX(selected+1)-12.0f;
			this->dispData->meshData->H_Knot_Intervals(selected) += (new_x-this->dispData->get_VertX(selected))*0.01f;
			glutPostRedisplay();
		}
		
		if (action == 21) { 
			if (new_y > this->dispData->get_VertY(selected-1)) new_y = this->dispData->get_VertY(selected-1)-12.0f;
			else if (new_y < this->dispData->get_VertY(selected+1)) new_y = this->dispData->get_VertY(selected+1)+12.0f;
			this->dispData->meshData->V_Knot_Intervals(selected) += (this->dispData->get_VertY(selected)-new_y)*0.01f;
			glutPostRedisplay();
		}
	}
}


void Scene2D::reshape(int width, int height)
{
	glViewport(0, 0, width, height); 			
	this->dispData->dispWdwWidth = width;
	this->dispData->dispWdwHeight = height;
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(0.0f, width, 0.0f, height, this->dispData->zOrthoMin, this->dispData->zOrthoMax); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
}



void Scene2D::display()	//----------------------------------------- GESTION DE L'AFFICHAGE
{
	/* Effacement de l'image avec la couleur de fond */
	glClearColor(this->dispData->bgColor[0], this->dispData->bgColor[1],
				 this->dispData->bgColor[2], this->dispData->bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Objets à afficher */
	glLoadIdentity();
	glPushMatrix();
		this->T_Grid->display();
		this->HK_Bar->display();
		this->VK_Bar->display();
		//this->Anchors->display();
	glPopMatrix();
	
	/* Nettoyage */
	glFlush();
	glutSwapBuffers();
}