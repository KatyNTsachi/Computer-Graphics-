#pragma once

#include"Point.h"
#include"Matrix.h"

class Line
{
public:
	Line(Point _p1, Point _p2);

	Line(double _x1, double _y1, double _z1, double _x2, double _y2, double _z2);
	~Line();
	Point getP1() const;
	Point getP2() const;
	void setP1(Point _p);
	void setP2(Point _p);
	Line tranformLine(Matrix tranformation_matrix);

	bool operator==(const Line &other) const;

private:
	Point p1, p2;
};

