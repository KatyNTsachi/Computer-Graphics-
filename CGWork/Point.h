#pragma once
class Point
{
public:
	Point();
	Point(double _x, double _y, double _z);
	~Point();
	double getX();
	double getY();
	void setX(double _x);
	void setY(double _y);
	void setZ(double _z);


private:
	double x, y, z;
};

