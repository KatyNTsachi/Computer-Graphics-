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
	/*
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
	*/
	return polygon_list;
}

std::vector<MyPolygon> Model::getBoundingBoxPolygons() {
	return bounding_box_polygon_list;
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

void Model::setBoundingBoxColor(COLORREF _color)
{
	boundingBoxColor = _color;
}

void Model::setNormalsColor(COLORREF _color)
{
	normalsColor = _color;
}

COLORREF Model::getModelColor() 
{
	return color;
}

COLORREF Model::getBoundingBoxColor()
{
	return boundingBoxColor;
}

Matrix Model::getTransformationMatrix()
{
	return objectSpaceTransformation * sceenSpaceTransformation;
}

void Model::scaleBy(Matrix scale_matrix)
{
	objectSpaceTransformation = objectSpaceTransformation * scale_matrix;
	//rotationTransformation.printMatrix();
}

void Model::transformInObjectSpace(Matrix _transformationnMatrix)
{
	objectSpaceTransformation = objectSpaceTransformation * _transformationnMatrix;
}

void Model::transformInViewSpace(Matrix _transformationnMatrix)
{
	sceenSpaceTransformation = sceenSpaceTransformation * _transformationnMatrix;
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

void Model::getMinMaxValues(double &_min_x, double &_max_x, double &_min_y, double &_max_y, double &_min_z, double &_max_z)
{
	_min_x = min_x;
	_max_x = max_x;
	_min_y = min_y;
	_max_y = max_y;
	_min_z = min_z;
	_max_z = max_z;

}

void Model::setShouldBoundingBox(bool _paint_bounding_box)
{
	paint_bounding_box = _paint_bounding_box;
}

bool Model::getShouldBoundingBox()
{
	return paint_bounding_box;
}

void Model::addNormals()
{
	for (auto tmp_polygon = polygon_list.begin(); tmp_polygon != polygon_list.end(); tmp_polygon++)
	{
		Point center = tmp_polygon->getCenter();
		Vector original_normal = tmp_polygon->getOriginalNormal();
		Vector calculated_normal = tmp_polygon->getCalculatedNormal();

		polygon_original_normal_list.push_back(Line(	Point(center.getX(), center.getY(), center.getZ()),
														Point(center.getX() + original_normal[0], center.getY() + original_normal[1] , center.getZ() + original_normal[2] )));

		polygon_calculated_normal_list.push_back(Line(	Point(center.getX(), center.getY(), center.getZ()),
									  					Point(center.getX() + calculated_normal[0], center.getY() + calculated_normal[1], center.getZ() + calculated_normal[2])));


		vector<Line> all_polygon_lines = tmp_polygon->getLines();
		for (auto tmp_line = all_polygon_lines.begin(); tmp_line != all_polygon_lines.end(); tmp_line++)
		{
			if (tmp_line->getP1() == polygon_list[0].getLines()[0].getP1())
			{
				int xxx = 0;
			}

			Vector point_original_normal = tmp_line->getP1().getOriginalNormal();
			Vector point_calculated_normal = tmp_line->getP1().getCalculatedNormal();

			vertex_original_normal_list.push_back(Line(	tmp_line->getP1(),
														Point(	tmp_line->getP1().getX() + point_original_normal[0],
																tmp_line->getP1().getY() + point_original_normal[1],
																tmp_line->getP1().getZ() + point_original_normal[2])));
			vertex_calculated_normal_list.push_back(Line(	tmp_line->getP1(),
															Point(	tmp_line->getP1().getX() + point_calculated_normal[0],
																	tmp_line->getP1().getY() + point_calculated_normal[1],
																	tmp_line->getP1().getZ() + point_calculated_normal[2])));

		}
	}


}


std::vector<Line> Model::getOriginalPoligonNormalList()
{
	return polygon_original_normal_list;
}

std::vector<Line> Model::getCalculatedPoligonNormalList()
{
	return polygon_calculated_normal_list;
}

std::vector<Line> Model::getOriginalVertexNormalList()
{
	return vertex_original_normal_list;
}

std::vector<Line> Model::getCalculatedVertexNormalList()
{
	return vertex_calculated_normal_list;
}

COLORREF Model::getNormalsColor()
{
	return normalsColor;
}

void Model::setListOfPolygons(std::vector<MyPolygon> _list_of_polygons)
{
	polygon_list = _list_of_polygons;
}