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
    //double & const operator [] (int index);
	~Vector();
private:
	double entries[4];
};


