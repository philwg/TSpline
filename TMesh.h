#ifndef TMESH
#define TMESH

#include <vector>
#include <armadillo>
#include "displayData.h"
#include "Scene2DElement.h"

class TMesh : public Scene2DElement {

	public :
	
		TMesh(displayData* dD_ptr);
		~TMesh();
		
		void display();	
		
	protected :
		
		std::vector<float*> get_Vertices();
		
	private :
	
		void displayNodes();		
		void displayHorizontalEdges();
		void displayVerticalEdges();
					
};

#endif