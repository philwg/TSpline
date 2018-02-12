#include "Data.h"

using namespace std;
using namespace arma;

/** Le constructeur des données ***************************************************
/*
/*	Initialisation des données dans Data.h
*/

Data::Data()
{}


/** Le destructeur des données ****************************************************
/* 
/*	Rien à détruire
*/
Data::~Data()
{}


/** Méthode d'accès à la matrice des noeuds actifs du TMesh ***********************
/*
/*	@return: le produit terme à terme des matrices d'arêtes
*/
umat Data::get_GridNodes()
{
	return this->H_Edges % this->V_Edges;
}

/** Méthode d'accès au nombre de lignes verticales du TMesh ***********************
*/
int Data::get_H_Width()
{
	return this->H_Knot_Intervals.n_elem; 
}

/** Méthode d'accès au nombre de lignes horizontales du TMesh ********************
*/
int Data::get_V_Height()
{
	return this->V_Knot_Intervals.n_elem;
}

/** Méthode d'accès au degré des fonctions de bases horizontales *****************
*/
int  Data::get_H_degree()
{
	return this->H_degree;
}

/** Méthode d'accès au degré des fonctions de bases verticales *******************
*/
int  Data::get_V_degree()
{
	return this->V_degree;
}

/** Méthode de modification du degré des fonctions de base dans la direction horizontale
*/
void Data::change_H_degree(int delta_Hd)
{
	this->H_degree += delta_Hd;
	if (this->H_degree < 1) this->H_degree = 1;
}

/** Méthode de modification du degré des fonctions de base dans la direction verticale
*/
void Data::change_V_degree(int delta_Vd)
{
	this->V_degree += delta_Vd;
	if (this->V_degree < 1) this->V_degree = 1;
}

/** Méthode d'accès aux valeurs courantes des noeuds horizontaux ****************
*/
vec Data::get_H_KnotValues()
{
	return cumsum(this->H_Knot_Intervals);
}

/**	Méthode d'accès aux valeurs courantes des noeuds verticaux ******************
*/
vec Data::get_V_KnotValues()
{
	return cumsum(this->V_Knot_Intervals);
}

/** Méthode qui renvoie le vecteur augmenté du dégré à gauche et à droite ******
/*	par répétition de la première et de la dernière valeur
*/
vec Data::completeKnotVector(vec KV, int deg)
{
	int size = KV.n_elem;
	vec Knots = vec(size + 2 * deg);
	for(int k=0; k < Knots.n_elem; k++) {
		if (k < deg) Knots(k) = KV(0);
		else {
			if (k > size + deg - 1) Knots(k) = KV(size - 1);
			else Knots(k) = KV(k - deg - 1);
		}
	}
	return Knots;
}

/**	Méthode d'accès au vecteur de noeud horizontal complété en fonction du degré
*/
vec Data::get_H_Knots()
{
	return this->completeKnotVector(this->get_H_KnotValues(), this->get_H_degree());
}
	
/** Méthode d'accès au vecteur de noeud vertical complété en fonction du degré
*/
vec Data::get_V_Knots()
{
	return this->completeKnotVector(this->get_V_KnotValues(), this->get_V_degree());
}