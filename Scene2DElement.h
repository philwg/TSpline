#ifndef SCENE_2D_ELT
#define SCENE_2D_ELT

#include <vector>
#include <GL/glut.h>
#include "displayData.h"

class Scene2DElement {

	public:
	
		Scene2DElement();
		Scene2DElement(displayData* dD_ptr);
		~Scene2DElement();
		
		virtual void display() = 0;
		int getPickedIndex(int mState, int x, int y);		
			
	protected:
	
		displayData* dispData;

		virtual std::vector<float*> get_Vertices() = 0;
		void renderBitmapString(float x, float y, void *font, const char *string);		
					
};

#endif