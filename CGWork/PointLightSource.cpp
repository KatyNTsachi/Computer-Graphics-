#include "PointLightSource.h"

PointLightSource::PointLightSource(Point _location, LightCoefficient _I_p)
{
	location = _location;
	I_p = _I_p;
}

Vector PointLightSource::getNormal(Point Objectlocation)
{
	Vector L = Vector(Objectlocation.getX() - location.getX(), Objectlocation.getY() - location.getY(), Objectlocation.getZ() - location.getZ(), 0);
	double norm = sqrt(pow(L[0],2) + pow(L[1], 2) + pow(L[2], 2));
	norm = (norm > 0) ? norm : 1;
	return Vector(L[0] / norm, L[1] / norm, L[2] / norm, 0);
}

LightCoefficient PointLightSource::getI_p(Point objectLocation)
{
	Vector L = Vector(objectLocation.getX() - location.getX(), objectLocation.getY() - location.getY(), objectLocation.getZ() - location.getZ(), 0);
	double norm = sqrt(pow(L[0], 2) + pow(L[1], 2) + pow(L[2], 2));
	double decay = (1 / norm);
	decay = (decay < 1) ? decay : 1;
	return I_p * (-log10(decay));
}
