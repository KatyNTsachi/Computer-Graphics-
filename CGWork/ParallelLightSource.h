#pragma once
#include "lightSource.h"

#include "Point.h"
#include "Vector.h"

class ParallelLightSource :
	public LightSource
{
public:
	ParallelLightSource();
	ParallelLightSource(Vector _normal);
	Vector getNormal(Point objectLocation);
	void setNormal(Vector _normal);
	LightCoefficient getI_p(Point objectLocation);
private:
	Vector normal;
};
