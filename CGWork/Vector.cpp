#include "Vector.h"

Vector::Vector() 
{
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
