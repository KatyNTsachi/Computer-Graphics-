#include "MyPolygon.h"
#include "Vector.h"
#include "Matrix.h"
#include "Line.h"


MyPolygon::MyPolygon()
{
	lines = std::vector<Line>();
}

MyPolygon::~MyPolygon()
{
}

void MyPolygon::addLine(Line line)
{
	lines.push_back(line);
}

std::vector<Line>& MyPolygon::getLines()
{
	return lines;
}


void MyPolygon::setCenter(Point _p)
{
	center_of_polygon = _p;
}

Point MyPolygon::getCenter()
{
	return center_of_polygon;
}

void MyPolygon::setOriginalNormal(Vector _normal)
{
	original_normal = _normal;
}

void MyPolygon::setCalculatedNormal(Vector _normal)
{
	calculated_normal = _normal;
}

Vector MyPolygon::getOriginalNormal()
{
	return original_normal;
}

Vector MyPolygon::getCalculatedNormal()
{
	return calculated_normal;
}

void MyPolygon::setListOfLines(std::vector<Line> _list_of_lines)
{
	lines = _list_of_lines;
}

MyPolygon MyPolygon::tranformPolygon(Matrix tranformation_matrix)
{
	MyPolygon new_poly;

	//calculate normal
	Vector N;
	Line tmp_Line = Line(Point(0, 0, 0), Point(N[0], N[1], N[2])).tranformLine(tranformation_matrix);
	N[0] = tmp_Line.getP2().getX() - tmp_Line.getP1().getX();
	N[1] = tmp_Line.getP2().getY() - tmp_Line.getP1().getY();
	N[2] = tmp_Line.getP2().getZ() - tmp_Line.getP1().getZ();
	new_poly.calculated_normal = N;

	new_poly.center_of_polygon = tranformation_matrix.getTranformation(this->center_of_polygon); // this->center_of_polygon * tranformation_matrix;

	return new_poly;
}