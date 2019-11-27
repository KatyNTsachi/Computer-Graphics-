#include "Model.h"


Model::Model()
{
	paint_bounding_box = false;
}

Model::~Model()
{
}

std::vector<MyPolygon> Model::getModelPolygons ()
{
	if (paint_bounding_box == false)
		return polygon_list;
	else
	{
		std::vector<MyPolygon> tmp_polygon;
		tmp_polygon = polygon_list;

		for(int i = 0; i < bounding_box_polygon_list.size(); i++)
			tmp_polygon.push_back(bounding_box_polygon_list[i]);

		return tmp_polygon;
	}
	
}

void Model::addPolygon(MyPolygon _polygon)
{
	polygon_list.push_back(_polygon);
}

void Model::addPolygonToBoundingBox(MyPolygon _polygon)
{
	bounding_box_polygon_list.push_back(_polygon);
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

Matrix Model::getTransformationMatrix()
{
	return rotationTransformation * affainTransformation;
}

void Model::addScaleMatrix(Matrix scale_matrix)
{
	rotationTransformation = rotationTransformation * scale_matrix;
	//rotationTransformation.printMatrix();
}

void Model::rotateBy(Matrix _rotationMatrix)
{
	rotationTransformation = rotationTransformation * _rotationMatrix;
}

void Model::translateBy(Matrix _affainMatrix) 
{
	affainTransformation = affainTransformation * _affainMatrix;
}

void Model::setMinMaxValues(double _min_x, double _max_x, double _min_y, double _max_y, double _min_z, double _max_z)
{
	min_x = _min_x;
	max_x = _max_x;
	min_y = _min_y;
	max_y = _max_y;
	min_z = _min_z;
	max_z = _max_z;
}

void Model::paintBoundingBox(bool _paint_bounding_box)
{
	paint_bounding_box = _paint_bounding_box;
}

