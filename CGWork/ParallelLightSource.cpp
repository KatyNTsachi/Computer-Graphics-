#include "ParallelLightSource.h"

ParallelLightSource::ParallelLightSource()
{
}

ParallelLightSource::ParallelLightSource(Vector _normal)
{
	normal = _normal;
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
