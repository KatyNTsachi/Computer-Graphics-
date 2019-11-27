#include "MyPolygon.h"



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
