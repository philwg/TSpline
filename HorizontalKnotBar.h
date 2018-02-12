#ifndef HORIZ_KNOT_BAR
#define HORIZ_KNOT_BAR

#include <vector>
#include "displayData.h"
#include "Scene2DElement.h"

class HorizontalKnotBar : public Scene2DElement {

	public:
	
		float Y;
		 
		HorizontalKnotBar(displayData* dD_ptr);
		~HorizontalKnotBar();
	
		void display();
		
	protected:
	
		std::vector<float*> get_Vertices();
			
};

#endif