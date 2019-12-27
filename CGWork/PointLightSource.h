#pragma once
#include "lightSource.h"

#include "Point.h"
#include "Vector.h"

class PointLightSource:
	public LightSource
{
public:
	PointLightSource();
	PointLightSource(Point location);
	Vector getNormal(Point Objectlocation);
	LightCoefficient getI_p(Point objectLocation);
private:
	Point location;
};
