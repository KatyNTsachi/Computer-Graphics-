#pragma once
#include "Resource.h"

class Vector
{
public:
	Vector();
	Vector(double x, double y, double z, double w);
	double operator * (Vector const &vector2);
	Vector operator * (double const _value);
	Vector operator + (Vector const &vector2);
	Vector operator - (Vector const &vector2);
	double &operator [] (int index);
	const double &operator [] (int index) const;
    bool const operator== (Vector const _vector);
	~Vector();
	Vector cross(Vector V2);
	double abs();
	void Normalize();


private:
	double entries[4];
};


