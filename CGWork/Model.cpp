#include "Model.h"



Model::Model()
{
}

Model::Model(std::vector<Line> line_list_new) 
{
	line_list = line_list_new;
}

Model::~Model()
{
}

std::vector<Line> Model::getModelLines(Matrix camera_transformation)
{
	return line_list;
}

void Model::addLine(Line _line)
{
	line_list.push_back(_line);
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