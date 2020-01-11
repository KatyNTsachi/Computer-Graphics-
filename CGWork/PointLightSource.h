#pragma once
#include "lightSource.h"

#include "Point.h"
#include "Vector.h"

class PointLightSource:
	public LightSource
{
public:
	PointLightSource();
	PointLightSource(Point location, LightCoefficient _I_p);
	Vector getNormal(Point Objectlocation);
	LightCoefficient getI_p(Point objectLocation);
	Vector getFlipNormal(Point Objectlocation);

	
private:
	Point location;
};

