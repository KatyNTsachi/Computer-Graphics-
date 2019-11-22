#include "Model.h"



Model::Model()
{
}

Model::~Model()
{
}

std::vector<Poligon> Model::getModelPoligons ()
{
	return poligon_list;
}

void Model::addPoligon(Poligon _poligon)
{
	poligon_list.push_back(_poligon);
}

void Model::setColor(COLORREF _color)
{
	color = _color;
}


void Model::setColor(int _RGB[])
{
	color = RGB(_RGB[0], _RGB[1], _RGB[2]);
}

COLORREF Model::getModelColor() 
{
	return color;
}

Matrix Model::getTransformation()
{
	return transformation;
}

void Model::addScaleMatrix(Matrix scale_matrix)
{
	transformation = transformation * scale_matrix;
	transformation.printMatrix();
}

