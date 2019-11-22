#include "Point.h"
#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <string.h>
using namespace std;

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

double Point::getZ()
{
	return z;
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

void Point::printPoint()
{
	string s = "point values are:   ";
	s += to_string(x) + "   ";
	s += to_string(y) + "   ";
	s += to_string(z) + "   ";

	std::wstring widestr = std::wstring(s.begin(), s.end());
	const wchar_t *c = widestr.c_str();
	AfxMessageBox(c, MB_OK);
}