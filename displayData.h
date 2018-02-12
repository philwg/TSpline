#ifndef DISPLAY_DATA
#define DISPLAY_DATA

#include "Data.h"

class displayData {

	public :
	
		int dispWdwXpos			= 60;		// Position de l'affichage en X
		int dispWdwYpos			= 60;		// Position de l'affichage en Y
		int dispWdwHeight		= 1200;		// Hauteur de l'affichage
		int dispWdwWidth		= 1200;		// Largeur de l'affichage
		int zOrthoMin			= -1;		// Profondeur minimum de l'affichage
		int zOrthoMax			= 1;		// Profondeur maximum de l'affichage
		float lnWidth			= 2.0f;		// Largeur d'affichage des lignes
		float pickingPrecision	= 12.0f;	// Précision du picking	
		
		float bgColor[4]	= {0.12f, 0.12f, 0.12f, 1.0f};	// Couleur d'arrière plan
		float ptSize[3]		= {7.0f, 9.0f, 13.0f};			// Taille d'affichage des points
		float Color[6][3]	= {	{0.72f, 0.36f, 0.18f},		// Couleurs utilisées dans l'interface
								{0.96f, 0.12f, 0.12f},
								{0.96f, 0.48f, 0.24f},
								{0.00f, 0.96f, 0.00f},
								{0.12f, 0.12f, 0.12f},
								{0.00f, 0.36f, 0.00f}  };

		Data* meshData;	// Pointeur sur les données définissant le TMesh
		
		displayData(Data* D_ptr);	// Constructeur de la classe
		~displayData();				// Destructeur de la classe
		
		float get_HSpan();
		float get_HDelta();
		float get_VSpan();
		float get_VDelta();
		
		float get_VertX(int H_index);
		float get_VertY(int V_index);
		float* get_Vertex(int H_index, int V_index);
		
};

#endif