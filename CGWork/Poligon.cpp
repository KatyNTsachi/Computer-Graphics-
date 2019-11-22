#include "Poligon.h"



Poligon::Poligon()
{
	lines = std::vector<Line>();
}

Poligon::~Poligon()
{
}

void Poligon::addLine(Line line)
{
	lines.push_back(line);
}

std::vector<Line> Poligon::getLines()
{
	return lines;
}
