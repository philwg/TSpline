#ifndef DATA
#define DATA

#include <armadillo>

class Data {

	public : 
	
		arma::umat H_Edges {{1, 1, 1, 1, 1, 1, 1, 1, 1},
							{0, 0, 0, 0, 0, 1, 1, 1, 1},
							{1, 1, 1, 1, 0, 0, 0, 0, 0},
							{0, 1, 1, 1, 1, 1, 1, 1, 1},
							{1, 1, 1, 0, 0, 0, 0, 0, 0},
							{0, 0, 1, 1, 1, 1, 0, 0, 0},
							{1, 1, 1, 0, 0, 1, 1, 1, 1},
							{0, 0, 0, 0, 1, 1, 1, 1, 1},
							{0, 0, 1, 1, 1, 1, 1, 0, 0},
							{1, 1, 1, 0, 0, 0, 1, 1, 1},
							{1, 1, 1, 1, 1, 1, 1, 1, 1}};

		arma::umat V_Edges {{1, 0, 0, 1, 0, 1, 0, 0, 1},
							{1, 0, 0, 1, 0, 1, 1, 0, 1},
							{1, 1, 1, 1, 0, 1, 1, 0, 1},
							{1, 1, 1, 1, 0, 1, 1, 1, 1},
							{1, 1, 1, 1, 0, 1, 0, 1, 1},
							{1, 0, 1, 1, 1, 1, 0, 1, 1},
							{1, 0, 1, 0, 1, 1, 0, 1, 1},
							{1, 0, 1, 0, 1, 1, 1, 0, 1},
							{1, 0, 1, 0, 1, 0, 1, 1, 1},
							{1, 0, 1, 0, 1, 0, 1, 0, 1},
							{1, 0, 1, 0, 1, 0, 1, 0, 1}};
		
		arma::vec H_Knot_Intervals {0, 1, 1, 1, 1, 1, 1, 1, 1};
		arma::vec V_Knot_Intervals {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
		
		Data();
		~Data();
				
		arma::umat get_GridNodes();
			
		arma::vec get_H_KnotValues();
		arma::vec get_V_KnotValues();
		arma::vec get_H_Knots();
		arma::vec get_V_Knots();
		
		int get_H_Width();
		int get_V_Height();
		
		int get_H_degree();
		int get_V_degree();
		
		void change_H_degree(int delta_Hd);
		void change_V_degree(int delta_Vd);
		
	private :
		
		int H_degree {3};
		int V_degree {3};
		
		arma::vec completeKnotVector(arma::vec KV, int deg);
		
};

#endif
