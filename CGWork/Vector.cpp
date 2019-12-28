#include "Vector.h"

Vector::Vector() 
{
	entries[0] = 0;
	entries[1] = 0;
	entries[2] = 0;
	entries[3] = 0;
}

Vector::Vector(double x, double y, double z, double w)
{
	entries[0] = x;
	entries[1] = y;
	entries[2] = z;
	entries[3] = w;
}

double Vector::operator * (Vector const &vector2) {
	double res = 0;
	for (int i = 0; i <4; i++) 
	{
		res += (entries[i] * vector2.entries[i]);
	}
	return res;
}

Vector Vector::operator + (Vector const &vector2) {
	Vector res;
	for (int i = 0; i < 4; i++)
	{
		res.entries[i] = (entries[i] + vector2.entries[i]);
	}
	return res;
}

Vector Vector::operator - (Vector const &vector2) {
	Vector res;
	for (int i = 0; i < 4; i++)
	{
		res.entries[i] = (entries[i] - vector2.entries[i]);
	}
	return res;
}

const double & Vector::operator [] (int index) const
{
	if (index < 0 || index > 3)
	{
		//std::cout << "Vector: index out of baunds";
		//return -1;
	}
	return entries[index];
}

double & Vector::operator [] (int index)
{
	if (index < 0 || index > 3)
	{
		//std::cout << "Vector: index out of baunds";
		//return -1;
	}
	return entries[index];
}


Vector::~Vector()
{
}

bool const Vector::operator== (Vector const _vector) 
{
	return (entries[0] == _vector.entries[0] && entries[1] == _vector.entries[1] && entries[2] == _vector.entries[2] && entries[3] == _vector.entries[3]);
}

Vector Vector::operator * (double const _value)
{
	Vector tmp_vector;
	tmp_vector[0] = entries[0] * _value;
	tmp_vector[1] = entries[1] * _value;
	tmp_vector[2] = entries[2] * _value;
	tmp_vector[3] = entries[3] * _value;
}



