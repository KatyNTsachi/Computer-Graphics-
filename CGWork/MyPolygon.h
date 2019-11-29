#pragma once

#include "Point.h"
#include "Line.h"
#include <vector>
#include "stdafx.h"
#include "Vector.h"

class MyPolygon
{

public:
	MyPolygon();
	~MyPolygon();
	void addLine(Line line);
	std::vector<Line> getLines();
	void setNormal(Vector _normal);
	void setCenter(Point _p);
	Point getCenter();
	Vector getNormal();

private:
	std::vector<Line> lines;
	Vector normal;
	Point center_of_polygon;
};

