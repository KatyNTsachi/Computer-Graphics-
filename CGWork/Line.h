#pragma once

#include"Point.h"

class Line
{
public:
	Line(Point _p1, Point _p2);
	Line(double _x1, double _y1, double _z1, double _x2, double _y2, double _z2);
	~Line();

private:
	Point p1, p2;
};

