#include "Transformations.h"
#include "Vector.h"
#include "stdafx.h"
#include "Resource.h"


Transformations::Transformations()
{
}

Transformations::~Transformations()
{
}

Matrix Transformations::translation(double _x, double _y, double _z)
{
	Matrix res_matrix(	Vector(1, 0, 0, _x),
						Vector(0, 1, 0, _y),
						Vector(0, 0, 1, _z),
						Vector(0, 0, 0, 1));
	return res_matrix;
}


Matrix Transformations::rotation(double _angle, int _axis)
{
	Matrix res_matrix;
	if (_axis == ID_AXIS_X)//x axis
	{
		res_matrix = Matrix(Vector(1, 0           , 0          , 0),
							Vector(0, cos(_angle) , sin(_angle), 0),
							Vector(0, -sin(_angle), cos(_angle), 0),
							Vector(0, 0           , 0          , 1));
	}
	else if (_axis == ID_AXIS_Y)//y axis
	{
		res_matrix = Matrix(Vector(cos(_angle), 0, -sin(_angle), 0),
							Vector(0          , 1, 0           , 0),
							Vector(sin(_angle), 0, 1           , cos(_angle)),
							Vector(0          , 0, 0           , 1));
	}
	else if(_axis == ID_AXIS_Z)//z axis
	{
		res_matrix = Matrix(Vector(cos(_angle) , sin(_angle), 0, 0),
							Vector(-sin(_angle), cos(_angle), 0, 0),
							Vector(0           , 0          , 1, 0) ,
							Vector(0           , 0          , 0, 1));
	}
	else
	{
		std::string  s = "the rotation axis is not leagal";
		std::wstring widestr = std::wstring(s.begin(), s.end());
		const wchar_t *c = widestr.c_str();
		AfxMessageBox(c, MB_OK);
	}
	return res_matrix;
}


Matrix Transformations::scale(double _x = 1, double _y = 1, double _z = 1)
{
	Matrix res_matrix(	Vector(_x, 0, 0, 0),
						Vector(0, _y, 0, 1),
						Vector(0, 0, _z, 1),
						Vector(0, 0, 0, 1));
	return res_matrix;
}