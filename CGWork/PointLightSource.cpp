#include "PointLightSource.h"

PointLightSource::PointLightSource(Point _location)
{
	location = _location;
}

Vector PointLightSource::getNormal(Point Objectlocation)
{
	return Vector(Objectlocation.getX() - location.getX(), Objectlocation.getY() - location.getY(), Objectlocation.getZ() - location.getZ(), 0);
}

LightCoefficient PointLightSource::getI_p(Point objectLocation)
{
	return I_p;
}
