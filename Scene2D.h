#ifndef SCENE_2D
#define SCENE_2D

#include <GL/glut.h>
#include "displayData.h"
// #include "AnchorSet.h"
#include "HorizontalKnotBar.h"
#include "VerticalKnotBar.h"
#include "TMesh.h"

class Scene2D {

	public :
	
		Scene2D(displayData* dD_ptr);
		~Scene2D();
		
		void showScene();
		
		void display();
		void menu(int item);
		void keyboard(unsigned char touche, int x, int y);
		void special(int key, int x, int y);
		void mouse(int mButton, int mState, int x, int y);
		void mousemotion(int x, int y);		
		void reshape(int width, int height);
				
	private :
	
		displayData* dispData;
		
		HorizontalKnotBar* HK_Bar;
		VerticalKnotBar* VK_Bar;
		TMesh* T_Grid;
		//AnchorSet Anchors;
		
		int action;
		int selected;
		int A_selected;
			
};

#endif
