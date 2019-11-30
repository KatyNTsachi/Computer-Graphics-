#pragma once
#include "Vector.h"

class Point
{
public:
	Point();
	Point(double _x, double _y, double _z);
	~Point();

	double getX() const;
    double getY() const;
	double getZ() const;

	bool operator==(const Point &other) const;

	void setX(double _x);
	void setY(double _y);
	void setZ(double _z);
	void printPoint();
	void setOriginalNormal(Vector _normal);
	void setCalculatedNormal(Vector _normal);
	Vector getOriginalNormal();
	Vector getCalculatedNormal();

private:
	double x, y, z;
	Vector original_normal;
	Vector calculated_normal;
};

