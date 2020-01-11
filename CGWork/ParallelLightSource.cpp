#include "ParallelLightSource.h"

ParallelLightSource::ParallelLightSource()
{
}

ParallelLightSource::ParallelLightSource(Vector _normal, LightCoefficient _I_p)
{
	normal = _normal;
	I_p = _I_p;
}


LightCoefficient ParallelLightSource::getI_p(Point objectLocation)
{
	return I_p;
}

void ParallelLightSource::setNormal(Vector _normal)
{
	normal = _normal;
}

Vector ParallelLightSource::getNormal(Point Objectlocation)
{
	return normal;
}

Vector ParallelLightSource::getFlipNormal(Point Objectlocation)
{
	return normal * (-1);
}

