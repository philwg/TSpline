#include "displayData.h"

#define PHI 0.618034f


/** Le constructeur des données d'affichage ***************************************
/*
/*	Initialisation des paramètres d'affichage
*/

displayData::displayData(Data* D_ptr)
{
	this->meshData = D_ptr;
}


/** Le destructeur des données d'affichage ****************************************
*/

displayData::~displayData()
{
	delete this->meshData;
}


float displayData::get_HSpan()
{
	return (PHI*this->dispWdwWidth)/sum(this->meshData->H_Knot_Intervals);
}

float displayData::get_HDelta()
{
	return ((1.0f-PHI)*2.0f*this->dispWdwWidth/3.0f);
}

float displayData::get_VSpan()
{
	return (PHI*this->dispWdwHeight)/sum(this->meshData->V_Knot_Intervals);
}

float displayData::get_VDelta()
{
	return ((1.0f-PHI)*1.0f*this->dispWdwHeight/3.0f);
}

float displayData::get_VertX(int H_index)
{
	return this->get_HSpan()*(this->meshData->get_H_KnotValues())(H_index)+this->get_HDelta();
}

float displayData::get_VertY(int V_index)
{
	return this->dispWdwHeight-(this->get_VSpan()*(this->meshData->get_V_KnotValues())(V_index)+this->get_VDelta());
}

float* displayData::get_Vertex(int H_index, int V_index)
{
	return new float[2] {this->get_VertX(H_index), this->get_VertY(V_index)};
}