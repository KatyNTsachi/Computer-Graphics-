#pragma once
class Vector
{
public:
	Vector();
	Vector(double x, double y, double z, double w);
	double operator * (Vector const &vector2);
	Vector operator + (Vector const &vector2);
	Vector operator - (Vector const &vector2);
	double &operator [] (int index);
	const double &operator [] (int index) const;
    bool const operator== (Vector const _vector);
	~Vector();
private:
	double entries[4];
};


