#include "Transformations.h"
#include "Vector.h"
#include "stdafx.h"
#include "Resource.h"
#define _USE_MATH_DEFINES
#include <math.h>


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
							Vector(sin(_angle), 0, cos(_angle) , 0),
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
		return Matrix();
	}
	return res_matrix;
}


Matrix Transformations::scale(double _x = 1, double _y = 1, double _z = 1)
{
	Matrix res_matrix(	Vector(_x, 0, 0, 0),
						Vector(0, _y, 0, 0),
						Vector(0, 0, _z, 0),
						Vector(0, 0, 0, 1));
	return res_matrix;
}


Matrix Transformations::inverseTranslation(double _x, double _y, double _z)
{
	Matrix res_matrix(	Vector(1, 0, 0, -_x),
						Vector(0, 1, 0, -_y),
						Vector(0, 0, 1, -_z),
						Vector(0, 0, 0, 1));
	return res_matrix;
}


Matrix Transformations::inverseRotation(double _angle, int _axis)
{
	Matrix res_matrix;
	if (_axis == ID_AXIS_X)//x axis
	{
		res_matrix = Matrix(Vector(1, 0, 0, 0),
							Vector(0, cos(-_angle), sin(-_angle), 0),
							Vector(0, -sin(-_angle), cos(-_angle), 0),
							Vector(0, 0, 0, 1));
	}
	else if (_axis == ID_AXIS_Y)//y axis
	{
		res_matrix = Matrix(Vector(cos(-_angle), 0, -sin(-_angle), 0),
							Vector(0, 1, 0, 0),
							Vector(sin(-_angle), 0, 1, cos(-_angle)),
							Vector(0, 0, 0, 1));
	}
	else if (_axis == ID_AXIS_Z)//z axis
	{
		res_matrix = Matrix(Vector(cos(-_angle), sin(-_angle), 0, 0),
							Vector(-sin(-_angle), cos(-_angle), 0, 0),
							Vector(0, 0, 1, 0),
							Vector(0, 0, 0, 1));
	}
	else
	{
		std::string  s = "the rotation axis is not leagal";
		std::wstring widestr = std::wstring(s.begin(), s.end());
		const wchar_t *c = widestr.c_str();
		AfxMessageBox(c, MB_OK);
		return Matrix();
	}
	return res_matrix;
}


Matrix Transformations::inverseScale(double _x = 1, double _y = 1, double _z = 1)
{
	Matrix res_matrix(	Vector(1/_x, 0, 0, 0),
						Vector(0, 1/_y, 0, 0),
						Vector(0, 0, 1/_z, 0),
						Vector(0, 0, 0, 1));
	return res_matrix;
}

Matrix Transformations::prespective(double alpha, double d)
{
	Matrix shift = Transformations::translation(0, 0, alpha + 1);
	Matrix shift_back = Transformations::translation(0, 0, -alpha - 1);
	Matrix perspectiveMatrix = Matrix(Vector(1, 0, 0, 0),
		Vector(0, 1, 0, 0),
		Vector(0, 0, d / (d - alpha), -alpha * d / (d - alpha)),
		Vector(0, 0, 1 / d, 0));
	Matrix mirorZ = Matrix(Vector(1, 0, 0, 0),
		Vector(0, 1, 0, 0),
		Vector(0, 0, -1, 0),
		Vector(0, 0, -0, 1));
	//return mirorZ * shift * perspectiveMatrix * shift_back * mirorZ;
	return shift * perspectiveMatrix * shift_back;

}

Vector Transformations::getNormalInTheMiddle(Vector N1, Vector N2, int steps, int i)
{

	//if there are no steps
	if (steps == 0)
		return N1;

	//
	Vector res_vec;

	//get the cross product
	Vector cross = N1.cross(N2);

	double dot_prod = N1 * N2;
	double cos_angle = std::abs(dot_prod) / (N1.abs() * N2.abs());
	double angle = acos(cos_angle);
	double rotate_angle = angle * ( ((double)i) / steps);

	Vector tmp_vec;

	// x axis
	tmp_vec[0] = cross[0];
	tmp_vec[1] = 0;
	tmp_vec[2] = cross[2];
	tmp_vec.Normalize();
	double alpha = acos(tmp_vec[0]);

	// y axis
	tmp_vec[0] = 0;
	tmp_vec[1] = cross[1];
	tmp_vec[2] = cross[2];
	tmp_vec.Normalize();
	double beta = acos(tmp_vec[1]);

	//correct angles 
	alpha = M_PI / 2 - alpha;
	beta = M_PI / 2 - beta;
	Matrix x_trans = Transformations::rotation(alpha, ID_AXIS_Y);
	Matrix y_trans = Transformations::rotation(beta, ID_AXIS_X);

	Matrix i_x_trans = Transformations::rotation(-alpha, ID_AXIS_X);
	Matrix i_y_trans = Transformations::rotation(-beta, ID_AXIS_Y);

	Matrix all_trans = x_trans * y_trans ;
	Matrix all_trans_inv = i_y_trans * i_x_trans;

	Matrix my_rotation = Transformations::rotation(-rotate_angle, ID_AXIS_Z);

	all_trans = all_trans * my_rotation;
	res_vec = all_trans.getTranformation(N1);
	res_vec = all_trans_inv.getTranformation(res_vec);

	return res_vec;
}