#ifndef VERT_KNOT_BAR
#define VERT_KNOT_BAR

#include <vector>
#include "displayData.h"
#include "Scene2DElement.h"

class VerticalKnotBar : public Scene2DElement {

	public:
	
		float X;

		VerticalKnotBar(displayData* dD_ptr);
		~VerticalKnotBar();
				
		void display();	
				
	protected:

		std::vector<float*> get_Vertices();
			
};

#endif