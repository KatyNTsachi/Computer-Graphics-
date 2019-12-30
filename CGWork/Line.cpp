#include "Line.h"



Line::Line(Point p1_new, Point p2_new)
{
	p1 = p1_new;
	p2 = p2_new;
}

Line::Line(double _x1, double _y1, double _z1, double _x2, double _y2, double _z2)
{
	p1 = Point(_x1, _y1, _z1);
	p2 = Point(_x2, _y2, _z2);
}

Line Line::tranformLine(Matrix tranformation_matrix)
{
	Point new_p1, new_p2;
	new_p1 = tranformation_matrix.getTranformation(p1);
	new_p2 = tranformation_matrix.getTranformation(p2);
	Line tranformed_line(new_p1, new_p2);
	return tranformed_line;
}


Line::~Line()
{
}

Point Line::getP1() const
{
	return p1;
}

Point Line::getP2() const
{
	return p2;
}

void Line::setP1(Point _p)
{
	p1 = _p;
}

void Line::setP2(Point _p)
{
	p2 = _p;
}

bool Line::operator==(const Line &other) const
{
	bool result;
	result = 
		((p1.getX() == other.p1.getX()
		&& p1.getY() == other.p1.getY()
		&& p1.getZ() == other.p1.getZ()) &&
		(p2.getX() == other.p2.getX()
		&& p2.getY() == other.p2.getY()
		&& p2.getZ() == other.p2.getZ())) ||
		((p1.getX() == other.p2.getX()
		&& p1.getY() == other.p2.getY()
		&& p1.getZ() == other.p2.getZ()) &&
		(p2.getX() == other.p1.getX()
		&& p2.getY() == other.p1.getY()
		&& p2.getZ() == other.p1.getZ()));
	return result;
}


Line Line::flipLine()
{
	return *this;
}