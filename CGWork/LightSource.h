#pragma once

#include "LightCoefficient.h"
#include "Point.h"
#include "Vector.h"

class LightSource
{
public:
	virtual Vector getNormal(Point objectLocation) = 0;
	virtual LightCoefficient getI_p(Point objectLocation) = 0;
protected:
	LightCoefficient I_p = LightCoefficient(255, 0, 0);
};

