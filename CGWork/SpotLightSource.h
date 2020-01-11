#pragma once
#include "LightSource.h"
#include "Point.h"
#include "Vector.h"
#include "iritSkel.h"

class SpotLightSource :
	public LightSource
{
public:
	SpotLightSource(Point _location, Vector _dir, LightCoefficient _I_p);
	Vector getNormal(Point Objectlocation);
	Vector getFlipNormal(Point Objectlocation);

	LightCoefficient getI_p(Point objectLocation);
private:
	Point location;
	Vector dir;
	double angle_th = M_PI / 7;
};

