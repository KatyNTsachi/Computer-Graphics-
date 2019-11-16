#include "Point.h"



Point::Point()
{
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Point::~Point()
{
}

double Point::getX() 
{
	return x;
}

double Point::getY()
{
	return y;
}

void Point::setX(double _x)
{
	x = _x;
}

void Point::setY(double _y)
{
	y = _y;
}

void Point::setZ(double _z)
{
	z = _z;
}