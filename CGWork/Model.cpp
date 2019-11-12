#include "Model.h"



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


