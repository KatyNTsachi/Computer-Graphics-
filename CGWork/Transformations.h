#pragma once
#include "Matrix.h"

class Transformations
{
public:
	Transformations();
	~Transformations();
	static Matrix translation(double _x, double _y, double _z);
	static Matrix rotation(double _angle, int _axis);
	static Matrix scale(double _x, double _y, double _z);
};

