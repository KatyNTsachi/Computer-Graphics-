#pragma once
class Point
{
public:
	Point();
	Point(double _x, double _y, double _z);
	~Point();
	double getX();
	double getY();
	double getZ();

	void setX(double _x);
	void setY(double _y);
	void setZ(double _z);
	void printPoint();


private:
	double x, y, z;
};

