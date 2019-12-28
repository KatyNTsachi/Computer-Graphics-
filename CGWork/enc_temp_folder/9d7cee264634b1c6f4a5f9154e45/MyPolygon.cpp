#include "MyPolygon.h"
#include "Vector.h"



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
