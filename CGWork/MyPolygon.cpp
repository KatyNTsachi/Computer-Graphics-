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

std::vector<Line> MyPolygon::getLines()
{
	return lines;
}

void MyPolygon::setNormal(Vector _normal)
{
	normal = _normal;
}


void MyPolygon::setCenter(Point _p)
{
	center_of_polygon = _p;
}

Point MyPolygon::getCenter()
{
	return center_of_polygon;
}

Vector MyPolygon::getNormal()
{
	return normal;
}
