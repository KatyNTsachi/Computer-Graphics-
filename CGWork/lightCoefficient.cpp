#include "lightCoefficient.h"

LightCoefficient::LightCoefficient()
{
	entries[0] = 0;
	entries[1] = 0;
	entries[2] = 0;
}

LightCoefficient::LightCoefficient(double x, double y, double z)
{
	entries[0] = x;
	entries[1] = y;
	entries[2] = z;
}

COLORREF LightCoefficient::operator * (LightCoefficient const &lightCoefficient2) {
	int R = lightCoefficient2.entries[0] * entries[0];
	int G = lightCoefficient2.entries[1] * entries[1];
	int B = lightCoefficient2.entries[2] * entries[2];
	return RGB(R, G, B);
}

LightCoefficient::~LightCoefficient()
{
}
