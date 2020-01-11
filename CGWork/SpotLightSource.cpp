#include "SpotLightSource.h"


SpotLightSource::SpotLightSource(Point _location, Vector _dir, LightCoefficient _I_p)
{
	location = _location;
	I_p = _I_p;
	dir = _dir;
	dir.Normalize();
}

Vector SpotLightSource::getNormal(Point Objectlocation)
{
	Vector L = Vector(Objectlocation.getX() - location.getX(), Objectlocation.getY() - location.getY(), Objectlocation.getZ() - location.getZ(), 0);
	Vector L_minus = L * (1);
	L_minus.Normalize();
	double angle = acos(L_minus * dir);
	if (abs(angle) <= angle_th)
	{
		L.Normalize();
		return L;
	}
	else
	{
		return Vector(0, 0, 0, 0);
	}

}

Vector SpotLightSource::getFlipNormal(Point Objectlocation)
{
	Vector L = Vector(Objectlocation.getX() - location.getX(), Objectlocation.getY() - location.getY(), Objectlocation.getZ() - location.getZ(), 0);
	Vector L_minus = L * (-1);
	L_minus.Normalize();
	return L_minus;
}


LightCoefficient SpotLightSource::getI_p(Point objectLocation)
{
	Vector L = Vector(objectLocation.getX() - location.getX(), objectLocation.getY() - location.getY(), objectLocation.getZ() - location.getZ(), 0);
	double norm = L.abs();
	Vector L_minus = L * (1);
	L_minus.Normalize();
	double angle = acos(L_minus * dir);
	
	L.Normalize();
	double decay = (1 / norm);
	decay = (decay < 1) ? decay : 1;
	if (abs(angle) <= angle_th)
	{
		return I_p * (-log10(decay));
	}
	else
	{
		return LightCoefficient(0,0,0);
	}
}